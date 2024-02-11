#ifndef NOT_EQUAL_TO_HPP
#define NOT_EQUAL_TO_HPP

#include "../Column.hpp"

template <typename Column>
class NotEqualTo
{
public:
    explicit NotEqualTo(const std::string& value) requires HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID != " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name != " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name != " + value;
            break;
        case ColumnType::Age:
            conditionString = "age != " + value;
            break;
        case ColumnType::Genre:
            conditionString = "genre != " + value;
            break;
        case ColumnType::Building:
            conditionString = "building != " + value;
            break;
        default:
            break;
        }
    }

    template<typename T>
    NotEqualTo (const T& value) requires CanToString<T> && HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID != " + std::to_string(value);
            break;
        case ColumnType::FirstName:
            conditionString = "first_name != " + std::to_string(value);
            break;
        case ColumnType::LastName:
            conditionString = "last_name != " + std::to_string(value);
            break;
        case ColumnType::Age:
            conditionString = "age != " + std::to_string(value);
            break;
        case ColumnType::Genre:
            conditionString = "genre != " + std::to_string(value);
            break;
        case ColumnType::Building:
            conditionString = "building != " + std::to_string(value);
            break;
        default:
            break;
        }
    }

    ~NotEqualTo() = default;
    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};


#endif