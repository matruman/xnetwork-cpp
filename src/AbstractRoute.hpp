#ifndef ABSTRACT_ROUTE_HPP
#define ABSTRACT_ROUTE_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include "Session.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class AbstractRoute
{
private:
    /* data */
public:
    virtual ~AbstractRoute() = default;
    virtual void resolve(http::request<http::string_body>& req,
        session::send_lambda& send_) = 0;
};

#endif