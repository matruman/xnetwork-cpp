#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <memory>
#include <string>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest, class Body, class Fields>
class message;
template<class CharT, class Traits, class Allocator>
struct basic_string_body;
template<class Allocator>
class basic_fields;

} // namespace http
} // namespace beast
} // namespace boost

// A proxy class for type boost::beast::http::request 
// It is made not to connect its header in other files
// and reduce compilation time and executable size
class HttpRequest
{
private:
    boost::beast::http::message<true, boost::beast::http::basic_string_body<
        char, std::char_traits<char>, std::allocator<char>>, 
        boost::beast::http::basic_fields<std::allocator<char>>> *msg;
public:
    HttpRequest();
    ~HttpRequest();

    std::string     method();
    std::string     target();
    std::string&    body();
    bool            keep_alive();
    bool            findHeader(std::string name);
    std::string     getHeader(std::string name);
    unsigned int    version();

    void            clear();

    boost::beast::http::message<true, boost::beast::http::basic_string_body<
        char, std::char_traits<char>, std::allocator<char>>, 
        boost::beast::http::basic_fields<std::allocator<char>>>* get();
};

#endif
