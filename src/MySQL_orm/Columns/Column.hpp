#ifndef COLUMN_HPP
#define COLUMN_HPP
#include <string>
#include "BaseColumn.hpp"

template <typename CRTP>
class Column : public BaseColumn
{
public:
    std::string getColumn()
    {
        return static_cast<CRTP*>(this)->getColumn();
    }
};

#endif
