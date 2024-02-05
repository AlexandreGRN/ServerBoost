#ifndef SELECT_HPP
#define SELECT_HPP
#include "../../libraries.hpp"
#include "../Tables/Table.hpp"

enum OperatorType
{
    And,
    Or
};

template <typename... Args>
class Select_ {
public:

    Select_(const TableType& tableType, Args... args)
    {
        SelectString = "SELECT * from " + Table{}.getTable(tableType) + " WHERE ";
        processArgs(args...);
    }
    ~Select_() = default;

    const std::string& retrieveSelectString() const
    {
        return SelectString;
    }

private:
    template <typename T>
    void makeFilterBody(const T& arg)
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
    void processSingleArg(const T& arg) {
        makeFilterBody(arg);
    }

    template <typename T, typename... Rest>
    void processSingleArg(const T& arg, Rest... rest) {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string SelectString = "";
    bool isFirstCondition = true;
};


#endif
