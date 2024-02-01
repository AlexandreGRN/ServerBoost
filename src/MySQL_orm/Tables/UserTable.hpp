#ifndef USER_TABLE_HPP
#define USER_TABLE_HPP

#include "../../libraries.hpp"
#include "Table.hpp"


class UserTable : public Table<UserTable>
{
public:
    std::string getTable() const
    {
        return "user";
    }
};

#endif