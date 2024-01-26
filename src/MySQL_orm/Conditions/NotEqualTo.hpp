#include "../../libraries.hpp"
#include "Condition.hpp"

class NotEqualTo : public Condition
{
public:
    NotEqualTo(std::string column, std::string value)
    {
        conditionString = column + " != " + value;
    }
    ~NotEqualTo() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};
