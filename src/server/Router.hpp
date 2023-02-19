#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <server/send_lambda.hpp>
#include <routes/AbstractRoute.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class Router
{
private:
    ApplicationContext &context;
    std::unordered_map<std::string, std::shared_ptr<AbstractRoute>>  routes;
public:
    Router(ApplicationContext &context);
    void    route(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_);

private:
    std::shared_ptr<AbstractRoute>  makeRoute(AbstractRoute *r);
};

#endif