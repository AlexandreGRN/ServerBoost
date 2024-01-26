#include "../../libraries.hpp"
#include "Condition.hpp"

class EqualTo : public Condition
{
public:
    EqualTo(std::string column, std::string value)
    {
        conditionString = column + " = " + value;
    }
    ~EqualTo() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};
