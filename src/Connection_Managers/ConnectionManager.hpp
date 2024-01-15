#include "../libraries.hpp"
#include "../ServerConnections/ServerConnection.hpp"

class ConnectionManager
{
public:
    ConnectionManager() = default;
    ~ConnectionManager() = default;

    // Add a connection
    void add_new_connection(auto socket)
    {
        std::shared_ptr<ServerConnection<ConnectionManager>> connection = std::make_shared<ServerConnection<ConnectionManager>>(std::move(socket), *this);
        connections.insert(connection.get());
        connection->start();
    }

    // Remove a connection
    void remove_connection(std::shared_ptr<ServerConnection<ConnectionManager>> connection)
    {
        connections.erase(connection.get());
    }

private:
    std::set<ServerConnection<ConnectionManager>*> connections;
};
