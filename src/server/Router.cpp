#include "Router.hpp"

Router::Router(std::shared_ptr<ApplicationContext> context) : context(context)
{
}

void    Router::addRoute(const char *path, std::unique_ptr<AbstractRoute> &&route)
{
    routes.emplace(path, std::move(route));
}


void    Router::route(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{
    auto it = routes.find(params.path());
    if (it == routes.end())
        throw std::invalid_argument("No route for requested path");
    
    std::unique_ptr<AbstractRoute> &resolver = it->second;
    resolver->resolve(req, params, session, send_);
}
