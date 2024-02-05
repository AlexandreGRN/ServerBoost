#ifndef GREATER_THAN_HPP
#define GREATER_THAN_HPP

#include "../Column.hpp"

template <typename Column>
class GreaterThan
{
public:
    explicit GreaterThan(const std::string& value) requires HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID > " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name > " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name > " + value;
            break;
        case ColumnType::Age:
            conditionString = "age > " + value;
            break;
        case ColumnType::Genre:
            conditionString = "genre > " + value;
            break;
        case ColumnType::Building:
            conditionString = "building > " + value;
            break;
        default:
            break;
        }
    }
    ~GreaterThan() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }

    std::string retrieveOperator() const { return "";}

    std::string conditionString;
};


#endif