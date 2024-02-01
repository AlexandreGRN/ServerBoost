#ifndef EQUAL_TO_HPP
#define EQUAL_TO_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class EqualTo : public Condition<EqualTo>
{
public:
    EqualTo(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " = '" + value + "'";
    }
    ~EqualTo() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif