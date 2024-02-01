#ifndef CONTAIN_HPP
#define CONTAIN_HPP

#include "Condition.hpp"
#include "../Columns/BaseColumn.hpp"

class Contain : public Condition<Contain>
{
public:
    Contain(const std::unique_ptr<BaseColumn>& column, const std::string& value)
    {
        conditionString = column->getColumn() + " LIKE '%" + value + "%'";
    }
    ~Contain() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

#endif