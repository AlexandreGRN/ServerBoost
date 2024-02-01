#ifndef GREATER_THAN_HPP
#define GREATER_THAN_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class GreaterThan : public Condition<GreaterThan>
{
public:
    GreaterThan(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " > " + value;
    }
    ~GreaterThan() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif