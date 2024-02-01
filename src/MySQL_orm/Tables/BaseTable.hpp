#ifndef BASETABLE_HPP
#define BASETABLE_HPP

#include "../../libraries.hpp"

class BaseTable
{
public:
    virtual std::string getTable() const {return "";}
};

#endif