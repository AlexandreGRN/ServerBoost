#ifndef GENRE_COLUMN_HPP
#define GENRE_COLUMN_HPP

#include "../Column.hpp"

class GenreColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Genre;
    }
};

#endif
