#include "../../libraries.hpp"

template <typename... Args>
class ANDFilter_
{
public:
    
    // Multiple conditions constructor
    ANDFilter_(Args... args)
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
    ~ANDFilter_() = default;

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
