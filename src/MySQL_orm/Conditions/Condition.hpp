#pragma once

#include "../../libraries.hpp"
#include "../mysql_orm_libraries.hpp"

class Condition
{
public:
    Condition() = default;
    ~Condition() = default;

    virtual std::string retrieveConditionString() = 0;
    std::string retrieveOperator()
    {
        return "";
    }
};

