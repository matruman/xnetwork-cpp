#ifndef SEND_LAMBDA_HPP
#define SEND_LAMBDA_HPP

#include <boost/beast/http.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class session;

// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
struct send_lambda
{
    session& self_;

    explicit send_lambda(session& self) : self_(self)
    {}

    void operator()(http::response<http::string_body>&& resp) const;
};

#endif