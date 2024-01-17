#include "../../libraries.hpp"
#include "Condition.hpp"

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
