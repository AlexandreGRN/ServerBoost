#ifndef TABLE_HPP
#define TABLE_HPP

#include "../../libraries.hpp"

enum class TableType
{
    User
};

class Table
{
public:
    const std::string getTable(const TableType& tableType) const
    {
        if (tableType == TableType::User)
            return "user";
        return "";
    }
};

#endif