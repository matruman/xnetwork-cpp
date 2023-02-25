#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <server/send_lambda.hpp>
#include <routes/AbstractRoute.hpp>
#include <iostream>

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>


class Router
{
private:
    ApplicationContext &context;
    std::unordered_map<std::string, std::shared_ptr<AbstractRoute>>  routes;
public:
    Router(ApplicationContext &context);
    void    route(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_);

private:
    std::shared_ptr<AbstractRoute>  makeRoute(AbstractRoute *r);
};

#endif