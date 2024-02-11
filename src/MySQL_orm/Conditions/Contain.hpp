#ifndef CONTAIN_HPP
#define CONTAIN_HPP

#include "../Column.hpp"

template <typename Column>
class Contain
{
public:
    explicit Contain(const std::string& value) requires HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '%" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '%" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '%" + value + "%'";
            break;
        case ColumnType::Age:
            conditionString = "age LIKE '%" + value + "%'";
            break;
        case ColumnType::Genre:
            conditionString = "genre LIKE '%" + value + "%'";
            break;
        case ColumnType::Building:
            conditionString = "building LIKE '%" + value + "%'";
            break;
        default:
            break;
        }
    }

    template<typename T>
    Contain (const T& value) requires CanToString<T> && HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '%" + std::to_string(value) + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '%" + std::to_string(value) + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '%" + std::to_string(value) + "%'";
            break;
        case ColumnType::Age:
            conditionString = "age LIKE '%" + std::to_string(value) + "%'";
            break;
        case ColumnType::Genre:
            conditionString = "genre LIKE '%" + std::to_string(value) + "%'";
            break;
        case ColumnType::Building:
            conditionString = "building LIKE '%" + std::to_string(value) + "%'";
            break;
        default:
            break;
        }
    }
    
    ~Contain() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};


#endif