#include "../../libraries.hpp"
#include "Condition.hpp"

class Contain : public Condition
{
public:
    Contain(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "%'";
    }
    ~Contain() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }
    std::string conditionString = "";
};
