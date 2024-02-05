#ifndef SELECT_HPP
#define SELECT_HPP
#include "../../libraries.hpp"
#include "../Tables/Table.hpp"

enum OperatorType
{
    And,
    Or
};

template <typename T>
concept HasFilterFunction = requires(T t) {
    { t.retrieveConditionString() } -> std::same_as<std::string>;
    { t.retrieveOperator() } -> std::same_as<std::string>;
};

template <typename... Args>
class Select_ {
public:

    Select_(const TableType& tableType, Args... args)
    {
        SelectString = "SELECT * FROM " + Table().getTable(tableType) + " WHERE ";
        processArgs(args...);
    }
    ~Select_() = default;

    const std::string& retrieveSelectString() const
    {
        return SelectString;
    }

private:
    template <typename T>
    void makeFilterBody(const T& arg) requires HasFilterFunction<T>
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            SelectString += arg.retrieveOperator();
        SelectString += arg.retrieveConditionString();
    }

    // Create the vector of argument strings
    void processArgs(Args... args) {processSingleArg(args...);}
    template <typename T>
    void processSingleArg(const T& arg) requires HasFilterFunction<T> {
        makeFilterBody(arg);
    }

    template <typename T, typename... Rest>
    void processSingleArg(const T& arg, Rest... rest) requires HasFilterFunction<T> {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string SelectString = "";
    bool isFirstCondition = true;
};


#endif
