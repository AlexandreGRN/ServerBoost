#ifndef BASE_CONDITION_HPP
#define BASE_CONDITION_HPP

#include <string>

class BaseCondition
{
public:
    virtual std::string retrieveConditionString() {return "";}
    virtual std::string retrieveOperator() const {return "";};
};

#endif