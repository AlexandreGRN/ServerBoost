#ifndef END_WITH_HPP
#define END_WITH_HPP

#include "../Column.hpp"

template <typename Column>
class EndWith
{
public:
    explicit EndWith(const std::string& value) requires HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '%" + value + "'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '%" + value + "'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '%" + value + "'";
            break;
        case ColumnType::Age:
            conditionString = "age LIKE '%" + value + "'";
            break;
        case ColumnType::Genre:
            conditionString = "genre LIKE '%" + value + "'";
            break;
        case ColumnType::Building:
            conditionString = "building LIKE '%" + value + "'";
            break;
        default:
            break;
        }
    }
    ~EndWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};


#endif