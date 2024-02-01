#ifndef NOT_EQUAL_TO_HPP
#define NOT_EQUAL_TO_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class NotEqualTo : public Condition<NotEqualTo>
{
public:
    NotEqualTo(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " != " + value;
    }
    ~NotEqualTo() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif