#ifndef NOT_CONTAIN_HPP
#define NOT_CONTAIN_HPP

#include "../Column.hpp"

template <typename Column>
class NotContain
{
public:
    NotContain(const std::string& value) requires HasGetColumn<Column>
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::Age:
            conditionString = "age NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::Genre:
            conditionString = "genre NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::Building:
            conditionString = "building NOT LIKE '%" + value + "%'";
            break;
        default:
            break;
        }
    }
    ~NotContain() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};


#endif