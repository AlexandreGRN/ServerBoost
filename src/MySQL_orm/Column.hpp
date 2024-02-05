#ifndef COLUMN_HPP
#define COLUMN_HPP
#include <string>

enum class ColumnType
{
    Id,
    FirstName,
    LastName,
    Age,
    Building,
    Genre
};

template <typename T>
concept HasGetColumn = requires(T t) { 
    { T{}.getColumn() } -> std::same_as<ColumnType>;
};

#endif
