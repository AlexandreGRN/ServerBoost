#include "../../libraries.hpp"
#include "Condition.hpp"

class EndWith : public Condition
{
public:
    EndWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "'";
    }
    ~EndWith() = default;

    std::string retrieveConditionString() override
    {
        return conditionString;
    }
    std::string conditionString = "";
};
