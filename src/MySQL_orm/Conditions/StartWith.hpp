#ifndef STARTWITH_HPP
#define STARTWITH_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class StartWith : public Condition<StartWith>
{
public:
    StartWith(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " LIKE '" + value + "%'";
    }
    ~StartWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif
