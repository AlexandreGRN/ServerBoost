#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>
/*
template <typename... Args>
class Select_ {
public:

    Select_(std::string table, Args... args)
    {
        SelectString = "SELECT * from " + table + " WHERE (";
        processArgs(args...);
    }
    ~Select_() = default;

    template<typename T>
    void makeFilterBody(T arg)
    {
        auto a = arg.retrieveArgList();
        for (auto i : a)
        {
            SelectString += i;
        }
    }

    // Create the vector of argument strings
    void processArgs(Args... args) {processSingleArg(args...);}
    void processSingleArg(std::string arg) {
        makeFilterBody(arg);
        SelectString += ")";
    }

    template <typename T, typename... Rest>
    void processSingleArg(T arg, Rest... rest) {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string result = "";
    std::vector<std::string> argList;
    std::string operator_ = "AND";
    std::string SelectString = "";
};
*/
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
            filterString += " " + arg.retrieveOperator() + " ";
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

    std::string operator_ = "AND";
    std::string filterString = "";
    bool isFirstCondition = true;
};

int main(int argc, char* argv[])
{

    Filter_ a(std::string("x < 0"));
    Filter_ b(std::string("y < 0"));
    Filter_ c(std::string("z < 0"));

    Filter_ d(std::string("x < 0"));
    Filter_ e(std::string("y < 0"));
    Filter_ f(std::string("z < 0"));

    Filter_ g(a, b, c);
    Filter_ h(d, e, f);
    Filter_ i(g, h);

    auto ww = i.retrieveConditionString();
    std::cout << ww << std::endl;
}
