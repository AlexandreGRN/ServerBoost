#ifndef ANDFILTER_HPP
#define ANDFILTER_HPP
#include "../../libraries.hpp"

template <typename... Args>
class ANDFilter_ final
{
public:
    /**
     * Multiple conditions or filters constructor (variadic)
     */
    explicit ANDFilter_(Args... args)
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
    ~ANDFilter_() = default;

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

#endif