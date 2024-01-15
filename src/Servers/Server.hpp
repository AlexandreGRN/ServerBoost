#include "../libraries.hpp"
#include "../Connection_Managers/ConnectionManager.hpp"

class Server
{
public:

    Server() = default;
    ~Server() = default;

    // Loop forever accepting new connections.
    void http_server(boost::asio::ip::tcp::acceptor& acceptor, boost::asio::ip::tcp::socket& socket)
    {
        // Make a new connection in a separate thread
        acceptor.async_accept(socket, [&](boost::beast::error_code ec)
        {
            if(!ec)
                connection_manager.add_new_connection(std::move(socket));
            http_server(acceptor, socket);
        });
    }

    void startServer(auto adress, auto port)
    {
        boost::asio::io_context ioc{1};
        boost::asio::ip::tcp::acceptor acceptor{ioc, {boost::asio::ip::tcp::v4(), 1025}};
        boost::asio::ip::tcp::socket socket{ioc};

        http_server(acceptor, socket);
        ioc.run();
    }

private:
    ConnectionManager connection_manager;
};
