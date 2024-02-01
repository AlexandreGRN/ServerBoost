#include "../libraries.hpp"
#include "../MySQL_orm/mysql_orm_libraries.hpp"
#include "../MySQL_orm/Actions/SelectFilter.hpp"

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

    std::vector<std::vector<std::string>> select_from_db(const std::string& filter)
    {
        std::vector<std::vector<std::string>> table;
        
        //std::string test = "['', 'condition', 'ID', '1', 'EqualTo'], ['OR', 'condition', 'ID', '0', 'GreaterThan'], ['OR', 'filter', ['', 'condition', 'ID', '1', 'EqualTo'], ['AND', 'condition', 'ID', '0', 'GreaterThan']]";
        SelectFilter converter(Select_{}, UserTable{}, filter);

        std::cout << converter.retrieveRequestString() << std::endl;

        pstmt = con->prepareStatement(converter.retrieveRequestString());
        res = pstmt->executeQuery();
        res->beforeFirst();
        while (res->next())
        {
            std::vector<std::string> row;
            row.push_back(res->getString("id"));
            row.push_back(res->getString("first_name"));
            row.push_back(res->getString("last_name"));
            row.push_back(res->getString("age"));
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
