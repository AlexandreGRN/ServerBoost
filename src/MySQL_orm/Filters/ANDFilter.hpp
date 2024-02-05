#ifndef ANDFILTER_HPP
#define ANDFILTER_HPP
#include "../../libraries.hpp"

template <typename... Args>
class ANDFilter_
{
public:
    // Multiple conditions constructor
    ANDFilter_(Args... args)
    {
        // Make minor filter
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

    std::string retrieveConditionString() const
    {
        return "(" + filterString + ")";
    }

    std::string retrieveOperator() const
    {
        if (operator_ == OperatorType::And)
            return " AND ";
        else
            return " OR ";
    }

private:

    // minor filter
    void makeGroupConditionString(const std::string& arg)
    {
        filterString += arg;
    }

    template<typename T>
    void makeGroupConditionString(const T& arg)
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
    }
    template <typename T, typename... Rest>
    void processSingleArg(const T arg, Rest... rest) {
        makeGroupConditionString(arg);
        processSingleArg(rest...);
    }

    OperatorType operator_ = And;
    std::string filterString = "";
    bool isFirstCondition = true;
};


#endif