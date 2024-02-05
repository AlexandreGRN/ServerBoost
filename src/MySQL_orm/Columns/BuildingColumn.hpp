#ifndef BUILDINGCOLUMN_HPP
#define BUILDINGCOLUMN_HPP

#include "../Column.hpp"

class BuildingColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Building;
    }
};

#endif
