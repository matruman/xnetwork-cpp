#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

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


class HttpResponse
{
public:
    enum status 
    {
        ok = 200,
        not_found = 404,
        bad_request = 400,
        internal_server_error = 500,
        unauthorized = 401
    };

private:
    boost::beast::http::message<false, boost::beast::http::basic_string_body<
        char, std::char_traits<char>, std::allocator<char>>, 
        boost::beast::http::basic_fields<std::allocator<char>>> *msg;
public:
    HttpResponse();
    HttpResponse(status s, unsigned int version);
    HttpResponse(HttpResponse &&res);

    ~HttpResponse();

    HttpResponse&   operator=(HttpResponse &&res);

    void            set(std::string name, const std::string &value);
    void            keep_alive(bool val);
    std::string&    body(); 
    void            prepare_payload();

    boost::beast::http::message<false, boost::beast::http::basic_string_body<
        char, std::char_traits<char>, std::allocator<char>>, 
        boost::beast::http::basic_fields<std::allocator<char>>>* get();
};

#endif
