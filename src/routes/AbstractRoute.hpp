#ifndef ABSTRACT_ROUTE_HPP
#define ABSTRACT_ROUTE_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <server/Session.hpp>
#include <server/ApplicationContext.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class AbstractRoute
{
private:
    ApplicationContext &context;
public:
    AbstractRoute(ApplicationContext &context);

    ApplicationContext& getContext() const;
    virtual ~AbstractRoute() = default;
    virtual void resolve(http::request<http::string_body>& req,
        session::send_lambda& send_) = 0;
};

#endif