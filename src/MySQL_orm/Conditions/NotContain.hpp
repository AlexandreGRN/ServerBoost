#include "../../libraries.hpp"
#include "Condition.hpp"

class NotContain : public Condition
{
public:
    NotContain(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "%'";
    }
    ~NotContain() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};

