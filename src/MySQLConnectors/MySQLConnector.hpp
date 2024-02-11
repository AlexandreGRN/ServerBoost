#include "../libraries.hpp"
#include "../MySQL_orm/mysql_orm_libraries.hpp"
#include "../MySQL_orm/Actions/Select.hpp"

class MySQLConnector
{
public:
    void connect(const std::string& ip, std::string user, std::string password, std::string database)
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://" + ip, user, password);
        con->setSchema(database);
    }

    void disconnect()
    {
        delete con;
    }

    std::vector<std::vector<std::string>> select_from_db(const auto& select)
    {
        std::vector<std::vector<std::string>> table;
        pstmt = con->prepareStatement(select.retrieveSelectString());
        res = pstmt->executeQuery();
        res->beforeFirst();
        while (res->next())
        {
            std::vector<std::string> row;
            row.push_back(res->getString("id"));
            row.push_back(res->getString("first_name"));
            row.push_back(res->getString("last_name"));
            row.push_back(res->getString("age"));
            if (res->getString("genre") == "0")
                row.push_back("M");
            else
                row.push_back("F");
            row.push_back(res->getString("building"));
            table.push_back(row);
        }
        delete res;
        delete pstmt;

        return table;
    }

private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
};
