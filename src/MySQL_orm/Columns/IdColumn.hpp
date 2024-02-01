#ifndef ID_COLUMN_HPP
#define ID_COLUMN_HPP

#include "Column.hpp"

class IdColumn : public Column<IdColumn>
{
public:
    std::string getColumn() const
    {
        return "id";
    }
};

#endif
