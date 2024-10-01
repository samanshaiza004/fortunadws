#include "Server.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

int main()
{
	try
	{

		int port = 8080;
		boost::asio::io_context io;
		Server server(io, port);
		std::cout << "now listening on port " << port << std::endl;
		server.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << "err: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}
