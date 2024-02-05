#ifndef SELECT_FILTER_HPP
#define SELECT_FILTER_HPP

#include "../../libraries.hpp"
#include "../Conditions/BaseCondition.hpp"
#include "../Filters/Filter.hpp"
#include "../Conditions/EqualTo.hpp"
#include "../Conditions/GreaterThan.hpp"
#include "../Conditions/LesserThan.hpp"
#include "../Conditions/NotEqualTo.hpp"
#include "../Conditions/StartWith.hpp"
#include "../Conditions/EndWith.hpp"
#include "../Conditions/Contain.hpp"
#include "../Conditions/NotContain.hpp"
#include "../Conditions/NotStartWith.hpp"
#include "../Conditions/NotEndWith.hpp"

#include "../Columns/user_libraries.hpp"

class SelectFilter
{
public:
    /**
     * Constructor: Convert a JSON request to a SQL request
    */
    SelectFilter(Select_&& action, BaseTable&& table, const std::string& requestFilter)
    {
        action.addFilter(table, *makeFilterString(0, requestFilter, requestFilter.size() - 1));
        requestString = action.retrieveSelectString();
    }
    ~SelectFilter() = default;

    const std::string& retrieveRequestString() const
    {
        return requestString;
    }

private:

    /**
     * Split a string with a delimiter
     * In: A string and a delimiter
     * Out: A vector of strings
    */
    std::vector<std::string>split(const std::string& input, const std::string& delims)
    {
        std::vector<std::string> ret;
        for (size_t start = 0, pos; ; start = pos + 1) {
            pos = input.find_first_of(delims, start);
            std::string token = input.substr(start, pos - start);
            if (token.length() > 0)  // ignore empty tokens
                ret.push_back(token);
            if (pos == std::string::npos) break;
        }
        return ret;
    }

    /**
     * Convert a string from the JSON request to a condition object
     * In: A string from the JSON request (as vector)
     * Out: A condition object
    */
    std::unique_ptr<BaseCondition> conditionConverter(const std::vector<std::string>& conditionVector){
        static const std::map<std::string, std::unique_ptr<BaseCondition>(*)(std::unique_ptr<BaseColumn>, const std::string&)> conditionMap = {
            {"Contain", &makeCondition<Contain>},
            {"NotContain", &makeCondition<NotContain>},
            {"StartWith", &makeCondition<StartWith>},
            {"EndWith", &makeCondition<EndWith>},
            {"NotStartWith", &makeCondition<NotStartWith>},
            {"NotEndWith", &makeCondition<NotEndWith>},
            {"EqualTo", &makeCondition<EqualTo>},
            {"NotEqualTo", &makeCondition<NotEqualTo>},
            {"GreaterThan", &makeCondition<GreaterThan>},
            {"LesserThan", &makeCondition<LesserThan>}
        };

        // Find the column type in the map
        static const std::map<std::string, std::unique_ptr<BaseColumn>(*)()> columnMap = {
            {"id", &makeColumn<IdColumn>},
            {"first_name", &makeColumn<FirstNameColumn>},
            {"last_name", &makeColumn<LastNameColumn>},
            {"age", &makeColumn<AgeColumn>},
            {"genre", &makeColumn<GenreColumn>},
            {"building", &makeColumn<BuildingColumn>}
        };
        auto it = conditionMap.find(conditionVector[4].substr(2, conditionVector[4].size() - 3));
        auto col = columnMap.find(conditionVector[2].substr(2, conditionVector[2].size() - 3));
        // If found in the map, call the function with the 2 args and return the result
        if (it != conditionMap.end() && col != columnMap.end())
            return it->second(col->second(), conditionVector[3].substr(2, conditionVector[3].size() - 3));
        else
            return std::make_unique<BaseCondition>();
    }

    /**
     * Make a condition object
     * In: The condition type and the 2 arguments
     * Out: A condition object
    */
    template <typename ConditionType>
    static std::unique_ptr<BaseCondition> makeCondition(std::unique_ptr<BaseColumn> arg1, const std::string& arg2) {
        return std::make_unique<ConditionType>(arg1, arg2);
    }

    /**
     * Make a column object
     * In: The column type
     * Out: A column object
    */
    template <typename ColumnType>
    static std::unique_ptr<BaseColumn> makeColumn() {
        return std::make_unique<ColumnType>();
    }
 
    /**
     * Convert a string from the JSON request to a filter object
     * Some filters can be nested
     * In: A string from the JSON request
     * Out: The filter object
    */
    std::unique_ptr<Filter_<>> makeFilterString(int starting_index, const std::string& requestFilter, int ending_index)
    {
        bool inFilter = false;
        int inFilterCount = 0;
        int start = 0;
        std::unique_ptr<Filter_<>> mfilter = std::make_unique<Filter_<>>();
        std::string filter;
        for (int i = starting_index; i <= ending_index; i++)
        {
            if (requestFilter[i] == '[')
            {
                inFilterCount += 1;
                if (!inFilter)
                    start = i;
                inFilter = true;
            }
            if (inFilter)
            {
                if (requestFilter[i] == ']')
                    inFilterCount -= 1;
                if (requestFilter[i] == ']' && inFilterCount == 0)
                {
                    // make filter
                    filter = requestFilter.substr(start + 1, i - start - 1);
                    inFilter = false;

                    std::vector<std::string> filter_vector = split(filter, ",");
                    std::unique_ptr<Filter_<>> filter_to_add = std::make_unique<Filter_<>>();
                    if (filter_vector[1] == " 'condition'")
                        filter_to_add->add_new_condition(conditionConverter(split(std::move(filter), ",")));
                    if (filter_vector[1] == " 'filter'")
                        filter_to_add = makeFilterString(start + 1, requestFilter, i - 1);
                    if (filter_vector[0] == "'OR'")
                        filter_to_add->setOperator(" OR ");
                    if (filter_vector[0] == "'AND'")
                        filter_to_add->setOperator(" AND ");
                    mfilter->add_new_condition(std::move(filter_to_add));
                }
            }
        }
        return mfilter;
    }

    std::string requestString = "";
};

#endif