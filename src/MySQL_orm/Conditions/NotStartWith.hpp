#include "../../libraries.hpp"
#include "Condition.hpp"

class NotStartWith : public Condition
{
public:
    NotStartWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '" + value + "%'";
    }
    ~NotStartWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};