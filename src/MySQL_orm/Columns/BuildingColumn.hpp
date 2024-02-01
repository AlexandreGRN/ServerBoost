#ifndef BUILDINGCOLUMN_HPP
#define BUILDINGCOLUMN_HPP

#include "Column.hpp"

class BuildingColumn : public Column<BuildingColumn>
{
public:
    std::string getColumn() const
    {
        return "building";
    }
};

#endif
