#ifndef LESSERTHAN_HPP
#define LESSERTHAN_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class LesserThan : public Condition<LesserThan>
{
public:
    LesserThan(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " < " + value;
    }
    ~LesserThan() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif