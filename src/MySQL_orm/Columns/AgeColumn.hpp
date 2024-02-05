#ifndef AGE_COLUMN_HPP
#define AGE_COLUMN_HPP

#include "../Column.hpp"

class AgeColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Age;
    }
};


#endif