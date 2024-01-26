#pragma once

#include "../../libraries.hpp"
#include "../mysql_orm_libraries.hpp"

class Condition
{
public:
    Condition() = default;
    ~Condition() = default;

    virtual std::string retrieveConditionString(){return "";}
    std::string retrieveOperator(){return "";}
};
