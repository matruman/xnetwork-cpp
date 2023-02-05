#include "Router.hpp"
#include <routes/GetOwnPosts.hpp>
#include <routes/UploadPost.hpp>

Router::Router(ApplicationContext &context) : context(context)
{
    routes.emplace("/getOwnPosts", makeRoute(new GetOwnPosts(context)));
    routes.emplace("/postSend", makeRoute(new UploadPost(context)));
}

void    Router::route(std::string path, http::request<http::string_body>& req,
        session::send_lambda& send_)
{
    auto it = routes.find(path);
    if (it == routes.end())
        throw std::invalid_argument("No route for requested path");
    
    std::shared_ptr<AbstractRoute> &resolver = it->second;
    resolver->resolve(req, send_);
}

std::shared_ptr<AbstractRoute>  Router::makeRoute(AbstractRoute *r)
{
    return std::shared_ptr<AbstractRoute>(r);
}
