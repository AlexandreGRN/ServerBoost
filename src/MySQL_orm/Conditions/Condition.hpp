#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "BaseCondition.hpp"

template <typename CRTP>
class Condition : public BaseCondition
{
public:
    std::string retrieveConditionString()
    {
        return static_cast<CRTP*>(this)->retrieveConditionString();
    }
    std::string retrieveOperator() const {return "";}
};

#endif