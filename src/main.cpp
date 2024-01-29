#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>
#include <memory>
#include <map>

template <typename... Args>
class Select_ {
public:

    Select_(std::string table, Args... args)
    {
        SelectString = "SELECT * from " + table + " WHERE ";
        processArgs(args...);
    }
    ~Select_() = default;

    std::string retrieveSelectString()
    {
        return SelectString;
    }

private:
    template <typename T>
    void makeFilterBody(T arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            SelectString += " " + arg.retrieveOperator() + " ";
        SelectString += arg.retrieveConditionString();
    }

    // Create the vector of argument strings
    void processArgs(Args... args) {processSingleArg(args...);}
    template <typename T>
    void processSingleArg(T arg) {
        makeFilterBody(arg);
    }

    template <typename T, typename... Rest>
    void processSingleArg(T arg, Rest... rest) {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string result = "";
    std::string SelectString = "";
    bool isFirstCondition = true;
};

class Condition
{
public:
    Condition() = default;
    ~Condition() = default;

    virtual std::string retrieveConditionString(){return "";}
    std::string retrieveOperator(){return "";}
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

    void setOperator(std::string op)
    {
        if (op == " AND " || op == " OR ")
            operator_ = op;
    }

private:

    /**
     * Make the filter with the arguments (as string)
     * In: A condition string
     */
    inline void makeGroupConditionString(std::string arg)
    {
        filterString += arg;
    }

    /**
     * Fill the filter with the arguments (as Condition or Filter object)
     * In: A condition or a filter object
     */ 
    template<typename T>
    void makeGroupConditionString(T arg)
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
    void processSingleArg(const T arg) {
        makeGroupConditionString(arg);
        filterString += ")";
    }
    template <typename T, typename... Rest>
    void processSingleArg(const T arg, Rest... rest) {
        makeGroupConditionString(arg);
        processSingleArg(rest...);
    }

    // Properties
    std::string operator_ = " AND ";
    std::string filterString = "";
    bool isFirstCondition = true;
};


class LesserThan : public Condition
{
public:
    LesserThan(std::string column, std::string value)
    {
        conditionString = column + " < " + value;
    }
    ~LesserThan() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class GreaterThan : public Condition
{
public:
    GreaterThan(std::string column, std::string value)
    {
        conditionString = column + " > " + value;
    }
    ~GreaterThan() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class EqualTo : public Condition
{
public:
    EqualTo(std::string column, std::string value)
    {
        conditionString = column + " = " + value;
    }
    ~EqualTo() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class NotEqualTo : public Condition
{
public:
    NotEqualTo(std::string column, std::string value)
    {
        conditionString = column + " != " + value;
    }
    ~NotEqualTo() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class StartWith : public Condition
{
public:
    StartWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '" + value + "%'";
    }
    ~StartWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class EndWith : public Condition
{
public:
    EndWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "'";
    }
    ~EndWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class NotStartWith : public Condition
{
public:
    NotStartWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '" + value + "%'";
    }
    ~NotStartWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class NotEndWith : public Condition
{
public:
    NotEndWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "'";
    }
    ~NotEndWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class Contain : public Condition
{
public:
    Contain(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "%'";
    }
    ~Contain() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

class NotContain : public Condition
{
public:
    NotContain(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "%'";
    }
    ~NotContain() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};




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
            return it->second(conditionVector[2].substr(1, conditionVector[2].size() - 1), conditionVector[3].substr(1, conditionVector[3].size() - 1));
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

    JsonToSQLCOnverter a("SELECT", "user", requestFilter);
    std::cout << a.retrieveRequestString() << std::endl;
}
