#include "libraries.hpp"
#include "Servers/Server.hpp"

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
 