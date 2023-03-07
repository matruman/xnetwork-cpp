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
    std::shared_ptr<ApplicationContext> context;
    std::unordered_map<std::string, std::unique_ptr<AbstractRoute>>  routes;
public:
    Router(std::shared_ptr<ApplicationContext> context);
    void    addRoute(const char *path, std::unique_ptr<AbstractRoute> &&route);
    void    route(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_);
};

#endif