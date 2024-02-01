#ifndef LASTNAMECOLUMN_HPP
#define LASTNAMECOLUMN_HPP

#include "Column.hpp"

class LastNameColumn : public Column<LastNameColumn>
{
public:
    std::string getColumn() const
    {
        return "last_name";
    }
};

#endif