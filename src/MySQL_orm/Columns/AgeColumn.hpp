#ifndef AGE_COLUMN_HPP
#define AGE_COLUMN_HPP

#include "Column.hpp"

class AgeColumn : public Column<AgeColumn>
{
public:
    std::string getColumn() const
    {
        return "age";
    }
};

#endif