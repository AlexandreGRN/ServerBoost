#include "../libraries.hpp"
#include "../MySQL_orm/mysql_orm_libraries.hpp"

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
        
        Select_ selection("user", Filter_(EqualTo("ID", "2")), ANDFilter_(StartWith("first_name", "prenom")), ORFilter_(EndWith("last_name", "nom2")));
        std::cout << selection.retrieveSelectString() << std::endl;
        pstmt = con->prepareStatement(selection.retrieveSelectString());
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

        Select_ selection("user", Filter_(EqualTo("ID", "1")));

        pstmt = con->prepareStatement(selection.retrieveSelectString());
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
