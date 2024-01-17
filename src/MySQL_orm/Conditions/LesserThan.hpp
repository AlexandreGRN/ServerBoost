#include "../../libraries.hpp"
#include "Condition.hpp"

class LesserThan : public Condition
{
public:
    LesserThan(std::string column, std::string value)
    {
        conditionString = column + " < " + value;
    }
    ~LesserThan() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }
    std::string conditionString = "";
};
