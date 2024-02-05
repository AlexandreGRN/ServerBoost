#ifndef LASTNAMECOLUMN_HPP
#define LASTNAMECOLUMN_HPP

#include "../Column.hpp"

class LastNameColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::LastName;
    }
};

#endif