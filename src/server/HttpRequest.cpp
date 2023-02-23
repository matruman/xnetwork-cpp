#include "HttpRequest.hpp"
#include <boost/beast/http.hpp>
#include <iostream>

#include <boost/url.hpp>
namespace urls = boost::urls;

extern urls::url_view *tmppar;

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

HttpRequest::HttpRequest()
{
    std::cout << "create http request" << std::endl;
    msg = new http::message<true, http::string_body>();
}

HttpRequest::~HttpRequest()
{
    std::cout << "delete http request" << std::endl;
    delete msg;
}

std::string     HttpRequest::method()
{
    if (msg->method() == http::verb::get)
        return "GET";
    if (msg->method() == http::verb::post)
        return "POST";
    return "UNKNOWN";
}

std::string     HttpRequest::target()
{
    return  msg->target();
}

std::string&    HttpRequest::body()
{
    return msg->body();
}

bool            HttpRequest::keep_alive()
{
    return msg->keep_alive();
}

bool            HttpRequest::findHeader(std::string name)
{

    std::cout << "fnd: " << tmppar->path() << "; name : ";
    std::cout.write(name.c_str(), 10);
    std::cout << std::endl;
    return msg->find(name) != msg->end();
}

std::string     HttpRequest::getHeader(std::string name)
{
    return msg->find(name)->value();
}

unsigned int    HttpRequest::version()
{
    return msg->version();
}

void            HttpRequest::clear()
{
    *msg = http::message<true, http::string_body>();
}

boost::beast::http::message<true, boost::beast::http::basic_string_body<
        char, std::char_traits<char>, std::allocator<char>>, 
        boost::beast::http::basic_fields<std::allocator<char>>>* HttpRequest::get()
{
    return msg;
}