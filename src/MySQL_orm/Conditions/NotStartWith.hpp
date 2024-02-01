#ifndef NOTSTARTWITH_HPP
#define NOTSTARTWITH_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class NotStartWith : public Condition<NotStartWith>
{
public:
    NotStartWith(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " NOT LIKE '" + value + "%'";
    }
    ~NotStartWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif