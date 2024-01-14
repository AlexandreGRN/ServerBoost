#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <set>
template<typename ConnectionManager>
class ServerConnection : public std::enable_shared_from_this<ServerConnection<ConnectionManager>>
{
public:
    ServerConnection(boost::asio::ip::tcp::socket socket, ConnectionManager connection_man) : socket_(std::move(socket)), connection_man(connection_man){}
    ~ServerConnection() = default;

    // Start server
    void start()
    {
        read_request();
        check_deadline();
    }

private:

    // Socket, buffer, request, response, and deadline timer
    boost::asio::ip::tcp::socket                                      socket_;
    boost::beast::flat_buffer                                         buffer_{8192};
    boost::beast::http::request<boost::beast::http::dynamic_body>     request_;
    boost::beast::http::response<boost::beast::http::dynamic_body>    response_;
    boost::asio::steady_timer                                         deadline_ {socket_.get_executor(), std::chrono::seconds(60) };
    ConnectionManager                                                 connection_man;

    // Read request
    void read_request()
    {
        std::shared_ptr<ServerConnection> self = this->shared_from_this();

        // Wait for a request and process it | async_read(read stream, buffer, the request, handler)
        boost::beast::http::async_read(socket_, buffer_, request_, [self](boost::beast::error_code ec, std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred); // Stop compiler complaint
            if(!ec)
                self->process_request();
        });
    }

    // Analyse request
    void process_request()
    {
        // Setyp response fields
        response_.version(request_.version());
        response_.keep_alive(false);

        if (request_.method() == boost::beast::http::verb::get) // If supported, return OK
        {
            response_.result(boost::beast::http::status::ok);
            response_.set(boost::beast::http::field::server, "Beast");
            create_response();
        }
        else                   // If not supported, return bad request
        {
            response_.result(boost::beast::http::status::bad_request);
            response_.set(boost::beast::http::field::content_type, "text/plain");
            boost::beast::ostream(response_.body()) << "Invalid request-method '" << std::string(request_.method_string()) << "'";
        }

        write_response();
    }

    // Construct a response message based on the route
    void create_response()
    {
        if(request_.target() == "/status")
        {
            response_.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(response_.body()) <<  "status: OK\n";
        }
        else
        {
            response_.result(boost::beast::http::status::not_found);
            response_.set(boost::beast::http::field::content_type, "text/plain");
            boost::beast::ostream(response_.body()) << "Route not found\r\n";
        }
    }

    // Transmit the response message.
    void write_response()
    {
        std::shared_ptr<ServerConnection> self = this->shared_from_this();

        response_.content_length(response_.body().size());

        connection_man.remove_connection(this->shared_from_this());

        boost::beast::http::async_write(
            socket_,
            response_,
            [self](boost::beast::error_code ec, std::size_t)
            {
                self->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
                self->deadline_.cancel();
            });
    }

    // Check whether we have spent enough time on this connection.
    void check_deadline()
    {
        std::shared_ptr<ServerConnection> self = this->shared_from_this();

        // Close server if deadline is reached
        deadline_.async_wait([self](boost::beast::error_code ec){
            if(!ec)
                self->socket_.close(ec);
        });
    }
};

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
        std::cout << "Connection removed: " << connections.size() << std::endl;
    }

private:
    std::set<ServerConnection<ConnectionManager>*> connections;
};


class Server
{
public:

    Server() = default;
    ~Server() = default;

    // Loop forever accepting new connections.
    void http_server(boost::asio::ip::tcp::acceptor& acceptor, boost::asio::ip::tcp::socket& socket)
    {
        // Make a new connection
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

int main(int argc, char* argv[])
{
    try
    {
        // Check command line arguments.
        if(argc != 3)
        {
            std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
            std::cerr << "127.0.0.1 1025\n";
            return EXIT_FAILURE;
        }

        Server server;
        server.startServer(boost::asio::ip::make_address(argv[1]), static_cast<unsigned short>(std::atoi(argv[2])));
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}