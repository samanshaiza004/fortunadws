#include "Server.hpp"
#include "HttpResponse.hpp"
Server::Server(boost::asio::io_context &io_context, int port)
    : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), port(port),
      work_guard_(boost::asio::make_work_guard(io_context)) // This will keep the io_context alive
{
  startAccept();
}

void Server::startAccept()
{
  auto socket = std::make_shared<tcp::socket>(io_context_);

  acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code &error)
                         {
                          std::cout << "Listening for connections on port " << port << std::endl;

        if (!error)
        {
            handleAccept(socket);
        }
        else
        {
            std::cerr << "Error accepting connection: " << error.message() << std::endl;
        }
        startAccept(); });
}

void Server::handleAccept(std::shared_ptr<tcp::socket> socket)
{
  boost::asio::socket_base::receive_buffer_size recv_option(16384);
  socket->set_option(recv_option);

  boost::asio::socket_base::send_buffer_size send_option(16384);
  socket->set_option(send_option);

  socket->set_option(boost::asio::socket_base::reuse_address(true));

  auto buffer = std::make_shared<boost::asio::streambuf>();
  asyncReadClient(socket, buffer);
}

void Server::asyncReadClient(std::shared_ptr<tcp::socket> socket, std::shared_ptr<boost::asio::streambuf> buffer)
{
  boost::asio::async_read_until(*socket, *buffer, "\r\n\r\n",
                                [this, socket, buffer](boost::system::error_code ec, std::size_t bytes_transferred)
                                {
                                  if (!ec)
                                  {
                                    std::istream requestStream(buffer.get());
                                    std::string request;
                                    std::getline(requestStream, request);
                                    std::cout << "Received request: " << request << std::endl;
                                    sendResponse(socket, request);
                                  }
                                  else
                                  {
                                    if (ec == boost::asio::error::operation_aborted)
                                    {
                                      std::cerr << "Operation aborted: " << ec.message() << std::endl;
                                    }
                                    else if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
                                    {
                                      std::cerr << "Client disconnected or connection reset" << std::endl;
                                    }
                                    else
                                    {
                                      std::cerr << "Error reading from client: " << ec.message() << std::endl;
                                    }
                                    socket->close();
                                  }
                                });
}

void Server::sendResponse(std::shared_ptr<tcp::socket> socket, const std::string &request)
{
  HttpResponse response;

  if (request.find("GET / ") != std::string::npos)
  {

    std::string htmlBody = "<html><body><h1>Welcome to my C++ server!</h1></body></html>";
    response.setBody(htmlBody);
  }
  else
  {

    response = HttpResponse(404, "Not Found");
    response.setBody("<html><body><h1>404 Not Found</h1></body></html>");
  }

  auto responseString = std::make_shared<std::string>(response.toString());

  boost::asio::async_write(*socket, boost::asio::buffer(*responseString),
                           [this, socket, response](boost::system::error_code ec, std::size_t /*length*/)
                           {
                             if (!ec)
                             {
                               boost::system::error_code shutdown_ec;
                               socket->shutdown(tcp::socket::shutdown_both, shutdown_ec);
                               if (shutdown_ec)
                               {
                                 std::cerr << "Shutdown error: " << shutdown_ec.message() << std::endl;
                               }
                               socket->close();
                             }
                             else
                             {
                               std::cerr << "Error sending response: " << ec.message() << std::endl;
                               socket->close();
                             }
                           });
}

void Server::run()
{
  std::vector<std::thread> threads;
  const std::size_t num_threads = 10;
  for (std::size_t i = 0; i < num_threads; ++i)
  {
    threads.emplace_back([this]()
                         { io_context_.run(); });
  }

  for (auto &thread : threads)
  {
    thread.join();
  }
}
