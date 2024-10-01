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

  void setBody(const std::string &body)
  {
    body_ = body;
    headers_["Content-Length"] = std::to_string(body.size());
  }

  void setHeader(const std::string &header, const std::string &value)
  {
    headers_[header] = value;
  }

  std::string toString() const
  {
    std::ostringstream responseStream;

    responseStream << "HTTP/1.1 " << statusCode_ << " " << statusMessage_ << "\r\n";

    for (const auto &header : headers_)
    {
      responseStream << header.first << ": " << header.second << "\r\n";
    }

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
