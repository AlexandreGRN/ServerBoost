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

    std::string retrieveConditionString()
    {
        return conditionString;
    }
    std::string conditionString = "";
};
