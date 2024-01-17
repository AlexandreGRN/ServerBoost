#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>

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

    virtual std::string retrieveConditionString() = 0;
    std::string retrieveOperator()
    {
        return "";
    }
};



template <typename... Args>
class Filter_
{
public:
    
    // Multiple conditions constructor
    Filter_(Args... args)
    {
        // Make minor filter
        filterString += "(";
        if (sizeof...(args) == 1)
        {
            processArgs(args...);
        }
        // Make major filter
        else
        {
            processArgs(args...);
        }
    }
    ~Filter_() = default;

    std::string retrieveConditionString()
    {
        return filterString;
    }

    std::string retrieveOperator()
    {
        return operator_;
    }

private:

    // minor filter
    void makeGroupConditionString(std::string arg)
    {
        filterString += arg;
    }

    template<typename T>
    void makeGroupConditionString(T arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            filterString += arg.retrieveOperator();
        filterString += arg.retrieveConditionString();
    }

    // Create the filter strings
    void processArgs(Args... args) {processSingleArg(args...);}
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
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

    std::string retrieveConditionString()
    {
        return conditionString;
    }
    std::string conditionString = "";
};


int main(int argc, char* argv[])
{
    /*
    Filter_ a(std::string("x < 0"));
    Filter_ b(std::string("y < 0"));
    Filter_ c(std::string("z < 0"));

    Filter_ d(std::string("x < 0"));
    Filter_ e(std::string("y < 0"));
    Filter_ f(std::string("z < 0"));

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

    Select_ a("user", Filter_(EqualTo("ID", "1"), Filter_(StartWith("first_name", "x")), Filter_(StartWith("last_name", "y"))));
    std::cout << a.retrieveSelectString() << std::endl;
    
}
