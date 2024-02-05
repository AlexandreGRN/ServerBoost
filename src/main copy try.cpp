#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>
#include <memory>
#include <map>
#include <chrono>

enum class TableName {
    User
};

enum class ColumnName {
    ID,
    FirstName,
    LastName
};

class UserTable
{
public:
    const std::string& getTable() const
    {
        return "user";
    }
};

class IdColumn
{
    const std::string& getColumn() const
    {
        return "ID";
    }
};

class FirstNameColumn
{
    const std::string& getColumn() const
    {
        return "first_name";
    }
};

class LastNameColumn
{
    const std::string& getColumn() const
    {
        return "last_name";
    }
};

class Select_ {
public:

    template <typename... Args>
    void addFilter(const BaseTable& table, Args... args)
    {
        static_assert(sizeof...(args) > 0, "You must provide at least one argument");
        SelectString = "SELECT * from " + table.getTable() + " WHERE ";
        processArgs(args...);
    }

    std::string retrieveSelectString() const
    {
        return SelectString;
    }

private:
    template <typename T>
    void makeFilterBody(T& arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            SelectString += " " + arg.retrieveOperator() + " ";
        SelectString += arg.retrieveConditionString();
    }

    // Create the vector of argument strings
    template <typename... Args>
    void processArgs(Args... args) {processSingleArg(args...);}
    template <typename T>
    void processSingleArg(T& arg) {
        makeFilterBody(arg);
    }

    template <typename T, typename... Rest>
    void processSingleArg(T& arg, Rest... rest) {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string result = "";
    std::string SelectString = "";
    int         nbArgs = 0;
    bool        isFirstCondition = true;
};

template <typename... Args>
class Filter_ final
{
public:
    /**
     * Multiple conditions or filters constructor (variadic)
     */
    explicit Filter_(Args... args)
    {
        // Make minor filter
        if (sizeof...(args) == 1)
        {
            processArgs(args...);
        }
        // Make major filter
        if (sizeof...(args) > 1)
        {
            processArgs(args...);
        }
    }
    ~Filter_() = default;

    /**
     * Retrieve the filter string
     * Out: "(x < 0 AND y < 0 AND z < 0)" (<- example)
    */
    inline std::string retrieveConditionString()
    {
        return  "(" + filterString + ")";
    }

    /**
     * Retrieve the filter operator
     * Out: " AND " or " OR "
    */
    inline std::string retrieveOperator()
    {
        return operator_;
    }

    /**
     * Add a new condition to the filter OR a new sub-filter to the filter
     * In: A unique pointer to a condition or a filter
    */
    template <typename T>
    void add_new_condition(std::unique_ptr<T> arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            filterString += arg->retrieveOperator();
        filterString += arg->retrieveConditionString();
    }

    void setOperator(const std::string& op)
    {
        if (op == " AND " || op == " OR ")
            operator_ = op;
    }

private:

    /**
     * Make the filter with the arguments (as string)
     * In: A condition string
     */
    inline void makeGroupConditionString(const std::string& arg)
    {
        filterString += arg;
    }

    /**
     * Fill the filter with the arguments (as Condition or Filter object)
     * In: A condition or a filter object
     */ 
    template<typename T>
    void makeGroupConditionString(T& arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            filterString += arg.retrieveOperator();
        filterString += arg.retrieveConditionString();
    }

    /**
     * Variadic template to process the arguments
     * In: A list of arguments
     */
    void processArgs(Args... args) {processSingleArg(args...);}
    void processSingleArg(){filterString += ")";}
    template <typename T>
    void processSingleArg(const T& arg) {
        makeGroupConditionString(arg);
        filterString += ")";
    }
    template <typename T, typename... Rest>
    void processSingleArg(const T& arg, Rest... rest) {
        makeGroupConditionString(arg);
        processSingleArg(rest...);
    }

    // Properties
    std::string operator_ = " AND ";
    std::string filterString = "";
    bool isFirstCondition = true;
};

template <typename Column>
class LesserThan
{
public:
    LesserThan(const int& value)
    {
        conditionString = Column{}.getColumn() + " < " + value;
    }
    LesserThan(const std::string& value)
    {
        conditionString = Column{}.getColumn() + " < " + value;
    }
    ~LesserThan() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

/* FilterString converter TO SQL Request string */
class FilterStringSelect
{
public:
    /**
     * Constructor: Convert a JSON request to a SQL request
    */
    template <typename Table>
    FilterStringSelect(Table&& table, const std::string& requestFilter)
    {
        requestString = "SELECT * from " + table.getTable() + " WHERE " + makeFilterString(0, requestFilter)->retrieveConditionString();
    }
    ~FilterStringSelect() = default;

    std::string retrieveRequestString()
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
   template <typename Column>
    std::string conditionConverter(const std::vector<std::string>& conditionVector){
        // Column
        static const std::map<>

        static const std::map<std::string, std::string(*)(const std::string&)> conditionMap = {
            {"LesserThan", &makeCondition<LesserThan<Column>>}
        };

        auto it = conditionMap.find(conditionVector[4].substr(2, conditionVector[4].size() - 3));
        // If found in the map, call the function with the 2 args and return the result
        if (it != conditionMap.end())
            return it->second(conditionVector[2].substr(1, conditionVector[2].size() - 1), conditionVector[3].substr(1, conditionVector[3].size() - 1));
        else
            return std::make_unique<BaseCondition>();
    }

    /**
     * Make a condition object
     * In: The condition type and the 2 arguments
     * Out: A condition object
    */
    template <typename ConditionType>
    static std::unique_ptr<BaseCondition> makeCondition(const std::string& arg1) {
        return std::make_unique<ConditionType>(arg1, arg2);
    }
 
    /**
     * Convert a string from the JSON request to a filter object
     * Some filters can be nested
     * In: A string from the JSON request
     * Out: The filter object
    */
    std::unique_ptr<Filter_<>> makeFilterString(int starting_index, const std::string& requestFilter)
    {
        bool inFilter = false;
        int inFilterCount = 0;
        int start = 0;
        std::unique_ptr<Filter_<>> mfilter = std::make_unique<Filter_<>>();
        std::string filter;
        for (int i = starting_index; i < requestFilter.size(); i++)
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
                        filter_to_add = makeFilterString(start + 1, requestFilter);
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



int main(int argc, char* argv[])
{
    /*
    Filter_ a(std::string("x < 0"));
    Filter_ b(std::string("y < 0"));
    Filter_ c(std::string("z < 0"));

    Filter_ d(std::string("x < 1"));
    Filter_ e(std::string("y < 1"));
    Filter_ f(std::string("z < 1"));

    Filter_ g(a, b, c);
    Filter_ h(d, e, f);
    Filter_ i(g, h);

    Select_ j("user" , i, d);

    std::cout << j.retrieveSelectString() << std::endl;
    */
    
    /*
    EqualTo a = EqualTo("ID", "1");
    Filter_ c = Filter_(a);

    Filter_ d = Filter_(StartWith("first_name", "x"));

    Filter_ e = Filter_(c, d);
    Select_ f = Select_("user", e);

    std::cout << f.retrieveSelectString() << std::endl;
 
    */


    /*Select_ a("user", Filter_(EqualTo("ID", "1"), Filter_(StartWith("first_name", "x")), Filter_(StartWith("last_name", "y"))));
    std::cout << a.retrieveSelectString() << std::endl;*/
    
    std::string requestFilter = "['', 'condition', 'ID', '1', 'EqualTo'], ['OR', 'condition', 'ID', '0', 'GreaterThan'], ['OR', 'filter', ['', 'condition', 'ID', '1', 'EqualTo'], ['AND', 'condition', 'ID', '0', 'GreaterThan']]";

    SelectFilter a(Select_{}, UserTable{}, requestFilter);
    std::cout << a.retrieveRequestString() << std::endl;
}
