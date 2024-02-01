#ifndef NOT_CONTAIN_HPP
#define NOT_CONTAIN_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class NotContain : public Condition<NotContain>
{
public:
    NotContain(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " NOT LIKE '%" + value + "%'";
    }
    ~NotContain() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif