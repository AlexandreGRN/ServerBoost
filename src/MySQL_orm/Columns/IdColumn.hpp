#ifndef ID_COLUMN_HPP
#define ID_COLUMN_HPP

#include "../Column.hpp"

class IdColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Id;
    }
};

#endif
