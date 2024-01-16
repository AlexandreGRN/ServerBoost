#include "../libraries.hpp"
#include "../MySQLConnectors/MySQLConnector.hpp"
#include "../Converters/JSonConverter.hpp"

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
    JSonConverter                                                     converter;

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

        if (request_.method() == boost::beast::http::verb::get || 
           request_.method() == boost::beast::http::verb::post ||
            request_.method() == boost::beast::http::verb::put ||
            request_.method() == boost::beast::http::verb::delete_
          ) // If supported, return OK
        {
            response_.result(boost::beast::http::status::ok);
            response_.set(boost::beast::http::field::server, "Beast");
            create_response();
        }
        else                                                     // If not supported, return bad request
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
        if(request_.target() == "/status" && request_.method() == boost::beast::http::verb::get)
        {
            response_.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(response_.body()) <<  "status: 200\n";
        }
        if (request_.target() == "/users_rapidjson" && request_.method() == boost::beast::http::verb::get)
        {
            // MySQLConnector
            MySQLConnector connector;
            connector.connect("127.0.0.1:3306", "user", "1234", "DB1");
            std::vector<std::vector<std::string>> users = connector.select_all_user();
            connector.disconnect();

            // Make response
            std::string str = converter.ToJson(users);
            response_.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(response_.body()) << str;
        }
        if (request_.target() == "/users_boostjson" && request_.method() == boost::beast::http::verb::get)
        {
            // MySQLConnector
            MySQLConnector connector;
            connector.connect("127.0.0.1:3306", "user", "1234", "DB1");
            std::vector<std::vector<std::string>> users = connector.select_all_user();
            connector.disconnect();

            // Make response
            boost::json::array jsonArray;
            boost::json::object jsonObject;
            
            for (int i = 0; i < users.size(); i++)
            {
                boost::json::object jsonObject;
                jsonObject["ID"]         = users[i][0];
                jsonObject["first_name"] = users[i][1];
                jsonObject["last_name"]  = users[i][2];
                jsonArray.push_back(jsonObject);
            }

            boost::json::value jsonValue = jsonArray;
            std::string str = serialize(jsonValue);
            std::cout << str << std::endl;
            response_.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(response_.body()) << str;
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
