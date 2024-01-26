#include "../../libraries.hpp"
#include "Condition.hpp"

class StartWith : public Condition
{
public:
    StartWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '" + value + "%'";
    }
    ~StartWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};
