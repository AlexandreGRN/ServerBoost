#ifndef NOT_END_WITH_HPP
#define NOT_END_WITH_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class NotEndWith : public Condition<NotEndWith>
{
public:
    NotEndWith(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " NOT LIKE '%" + value + "'";
    }
    ~NotEndWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif