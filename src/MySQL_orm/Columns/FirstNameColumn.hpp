#ifndef MYSQL_ORM_COLUMNS_FIRSTNAMECOLUMN_HPP
#define MYSQL_ORM_COLUMNS_FIRSTNAMECOLUMN_HPP

#include "Column.hpp"

class FirstNameColumn : public Column<FirstNameColumn>
{
public:
    std::string getColumn() const
    {
        return "first_name";
    }
};

#endif