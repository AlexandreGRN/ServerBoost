#include "../../libraries.hpp"

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
