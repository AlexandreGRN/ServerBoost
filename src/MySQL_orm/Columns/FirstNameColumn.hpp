#ifndef MYSQL_ORM_COLUMNS_FIRSTNAMECOLUMN_HPP
#define MYSQL_ORM_COLUMNS_FIRSTNAMECOLUMN_HPP

#include "../Column.hpp"

class FirstNameColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::FirstName;
    }
};

#endif