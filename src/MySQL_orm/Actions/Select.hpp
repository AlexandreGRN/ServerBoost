#ifndef SELECT_HPP
#define SELECT_HPP
#include "../../libraries.hpp"
#include "../Tables/BaseTable.hpp"

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

#endif
