#include "../libraries.hpp"

class MySQLConnector
{
public:
    MySQLConnector() = default;
    ~MySQLConnector() = default;

    void connect(std::string ip, std::string user, std::string password, std::string database)
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://" + ip, user, password);
        con->setSchema(database);
    }

    void disconnect()
    {
        delete con;
    }

    std::vector<std::vector<std::string>> select_all_user()
    {
        std::vector<std::vector<std::string>> table;
        
        pstmt = con->prepareStatement("SELECT * FROM user WHERE (ID = 1 AND (ID > 0 AND ID < 10) AND (ID < 20))");
        res = pstmt->executeQuery();
        res->beforeFirst();
        while (res->next())
        {
            std::vector<std::string> row;
            row.push_back(res->getString("ID"));
            row.push_back(res->getString("first_name"));
            row.push_back(res->getString("last_name"));
            table.push_back(row);
        }
        delete res;
        delete pstmt;

        return table;
    }

    std::vector<std::string> select_element(std::string column, std::string value)
    {
        std::vector<std::string> row;

        pstmt = con->prepareStatement("SELECT * FROM user WHERE ID = 1");
        res = pstmt->executeQuery();

        if (res->next()) {
            row.push_back(res->getString("ID"));
            row.push_back(res->getString("first_name"));
            row.push_back(res->getString("last_name"));
        }
        delete res;
        delete pstmt;

        return row;
    }

private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
};
