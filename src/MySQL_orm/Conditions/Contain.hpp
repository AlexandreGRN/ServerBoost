#ifndef CONTAIN_HPP
#define CONTAIN_HPP

#include "../Column.hpp"

template <typename Column>
class Contain
{
public:
    Contain(const std::string& value)
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
    ~Contain() = default;

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }
    
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};


#endif