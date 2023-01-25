#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "AbstractRoute.hpp"
#include "DefaultRoute.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
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
    std::unordered_map<std::string, std::shared_ptr<AbstractRoute>>  routes;
public:
    Router()
    {
        AbstractRoute *p = new DefaultRoute();
        std::shared_ptr<AbstractRoute> sp(p);
        routes.emplace("/", sp);
    }

    void    route(std::string path, http::request<http::string_body>& req,
        session::send_lambda& send_)
    {

        auto it = routes.find(path);
        if (it == routes.end())
            throw std::invalid_argument("No route for requested path");
        
        std::shared_ptr<AbstractRoute> &resolver = it->second;
        resolver->resolve(req, send_);
    }
};

#endif