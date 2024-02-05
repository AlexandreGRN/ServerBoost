#ifndef FILTER_HPP
#define FILTER_HPP
#include "../../libraries.hpp"

template <typename... Args>
class Filter_
{
public:
    // Multiple conditions constructor
    Filter_(Args... args)
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
    ~Filter_() = default;

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
    void makeGroupConditionString(const T& arg) requires HasFilterFunction<T>
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
    void processSingleArg(const T arg) requires HasFilterFunction<T> {
        makeGroupConditionString(arg);
    }
    template <typename T, typename... Rest>
    void processSingleArg(const T arg, Rest... rest) requires HasFilterFunction<T> {
        makeGroupConditionString(arg);
        processSingleArg(rest...);
    }

    OperatorType operator_ = And;
    std::string filterString = "";
    bool isFirstCondition = true;
};

#endif