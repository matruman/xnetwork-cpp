#include "HttpResponse.hpp"
#include <boost/beast/http.hpp>
#include <stdexcept>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

HttpResponse::HttpResponse()
{
    msg = nullptr;
}

HttpResponse::HttpResponse(status s, unsigned int version)
{
    if (s == ok)
        msg = new http::response<http::string_body>(http::status::ok, version);
    else if (s == not_found)
        msg = new http::response<http::string_body>(http::status::not_found, version);
    else if (s == bad_request)
        msg = new http::response<http::string_body>(http::status::bad_request, version);
    else if (s == internal_server_error)
        msg = new http::response<http::string_body>(http::status::internal_server_error, version);
    else if (s == unauthorized)
        msg = new http::response<http::string_body>(http::status::unauthorized, version);
    else
        throw std::invalid_argument("unknown response status");
}

HttpResponse::HttpResponse(HttpResponse &&res)
{
    msg = res.msg;
}


HttpResponse::~HttpResponse()
{
    if (msg != nullptr)
        delete msg;
}

HttpResponse&   HttpResponse::operator=(HttpResponse &&res)
{
    if (msg != nullptr)
        delete msg;
    msg = res.msg;
    res.msg = nullptr;
    return *this;
}

void            HttpResponse::set(std::string name, const std::string &value)
{
    msg->set(name, value);
}

void            HttpResponse::keep_alive(bool val)
{
    msg->keep_alive(val);
}

std::string&    HttpResponse::body()
{
    return msg->body();
}

void            HttpResponse::prepare_payload()
{
    msg->prepare_payload();
}

http::message<false, http::basic_string_body<
    char, std::char_traits<char>, std::allocator<char>>, 
    http::basic_fields<std::allocator<char>>>*    HttpResponse::get()
{
    return msg;
}
