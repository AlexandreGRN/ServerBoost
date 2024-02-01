#ifndef END_WITH_HPP
#define END_WITH_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class EndWith : public Condition<EndWith>
{
public:
    EndWith(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " LIKE '%" + value + "'";
    }
    ~EndWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif