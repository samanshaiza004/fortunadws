#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <map>
#include <sstream>

class HttpResponse
{
public:
  HttpResponse(int statusCode = 200, const std::string &statusMessage = "OK")
      : statusCode_(statusCode), statusMessage_(statusMessage)
  {
    headers_["Content-Type"] = "text/html";
    headers_["Connection"] = "close";
  }

  // Set the response body and update Content-Length
  void setBody(const std::string &body)
  {
    body_ = body;
    headers_["Content-Length"] = std::to_string(body.size());
  }

  // Set custom headers
  void setHeader(const std::string &header, const std::string &value)
  {
    headers_[header] = value;
  }

  // Convert the HttpResponse object into a valid HTTP response string
  std::string toString() const
  {
    std::ostringstream responseStream;

    // Correct HTTP version: "HTTP/1.1"
    responseStream << "HTTP/1.1 " << statusCode_ << " " << statusMessage_ << "\r\n";

    // Append headers
    for (const auto &header : headers_)
    {
      responseStream << header.first << ": " << header.second << "\r\n";
    }

    // Separate headers from body
    responseStream << "\r\n"
                   << body_;

    return responseStream.str();
  }

private:
  int statusCode_;
  std::string statusMessage_;
  std::map<std::string, std::string> headers_;
  std::string body_;
};

#endif
