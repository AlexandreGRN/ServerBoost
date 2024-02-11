#ifndef COLUMN_HPP
#define COLUMN_HPP
#include <string>
#include <stdexcept>
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

template <typename T>
concept CanToString = requires(T t) {
    { std::to_string(t) } -> std::convertible_to<std::string>;
};

#endif
