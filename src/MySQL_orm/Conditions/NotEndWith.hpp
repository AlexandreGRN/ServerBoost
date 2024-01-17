#include "../../libraries.hpp"
#include "Condition.hpp"

class NotEndWith : public Condition
{
public:
    NotEndWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "'";
    }
    ~NotEndWith() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }
    std::string conditionString = "";
};
