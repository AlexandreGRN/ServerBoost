#ifndef TABLE_HPP
#define TABLE_HPP

#include "../../libraries.hpp"
#include "BaseTable.hpp"

template <typename CRTP>
class Table : public BaseTable
{
public:
    std::string getTable()
    {
        return static_cast<CRTP*>(this)->getTable();
    }
};

#endif