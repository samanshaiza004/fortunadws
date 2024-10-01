#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <thread>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_context &io_context, int port);
    void run();

private:
    void startAccept();
    void handleAccept(std::shared_ptr<tcp::socket> socket);
    void asyncReadClient(std::shared_ptr<tcp::socket> socket, std::shared_ptr<boost::asio::streambuf> buffer);
    void sendResponse(std::shared_ptr<tcp::socket> socket, const std::string &request);

    boost::asio::io_context &io_context_;
    tcp::acceptor acceptor_;
    int port;

    // Adding work guard to prevent io_context from stopping early
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard_;
};

#endif
