#ifndef GENRE_COLUMN_HPP
#define GENRE_COLUMN_HPP

#include "Column.hpp"

class GenreColumn : public Column<GenreColumn>
{
public:
    std::string getColumn() const
    {
        return "genre";
    }
};

#endif
