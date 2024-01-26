#include "../../libraries.hpp"

/* FilterString converter TO SQL Request string */
class JsonToSQLCOnverter
{
public:


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
    std::unique_ptr<Condition> conditionConverter(std::vector<std::string> conditionVector){
        static const std::map<std::string, std::unique_ptr<Condition>(*)(const std::string&, const std::string&)> conditionMap = {
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

        auto it = conditionMap.find(conditionVector[4].substr(2, conditionVector[4].size() - 3));
        // If found in the map, call the function with the 2 args and return the result
        if (it != conditionMap.end())
            return it->second(conditionVector[2].substr(1, conditionVector[2].size() - 1), conditionVector[3].substr(2, conditionVector[3].size() - 3));
        else
            return std::make_unique<Condition>();
    }

    /**
     * Make a condition object
     * In: The condition type and the 2 arguments
     * Out: A condition object
    */
    template <typename ConditionType>
    static std::unique_ptr<Condition> makeCondition(const std::string& arg1, const std::string& arg2) {
        return std::make_unique<ConditionType>(arg1, arg2);
    }
 
    /**
     * Convert a string from the JSON request to a filter object
     * Some filters can be nested
     * In: A string from the JSON request
     * Out: The filter object
    */
    std::unique_ptr<Filter_<>> makeFilterString(std::string requestFilter)
    {
        //Filter_ new_filter;
        bool inFilter = false;
        int inFilterCount = 0;
        int start = 0;
        std::unique_ptr<Filter_<>> mfilter = std::make_unique<Filter_<>>();
        std::string filter;
        for (int i = 0; i < requestFilter.size(); i++)
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
                        filter_to_add = makeFilterString(filter);
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

    /**
     * Constructor: Convert a JSON request to a SQL request
    */
    JsonToSQLCOnverter(std::string action, std::string table, std::string requestFilter)
    {
        if (action == "SELECT"){
            Select_ select(table, *makeFilterString(requestFilter));
            requestString = select.retrieveSelectString();
        }
    }
    ~JsonToSQLCOnverter() = default;

    std::string retrieveRequestString()
    {
        return requestString;
    }


private:
    std::string requestString = "";
    std::string filterString = "";
};
