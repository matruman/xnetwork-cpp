#include "Router.hpp"
#include <routes/AuthCheck.hpp>
#include <routes/AuthRoute.hpp>
#include <routes/GetChatList.hpp>
#include <routes/GetChatMessages.hpp>
#include <routes/GetNewMessages.hpp>
#include <routes/GetOwnPosts.hpp>
#include <routes/GetUserList.hpp>
#include <routes/SendMessageRoute.hpp>
#include <routes/RegistrationRoute.hpp>
#include <routes/UploadPost.hpp>

Router::Router(ApplicationContext &context) : context(context)
{
    routes.emplace("/auth", makeRoute(new AuthRoute(context)));
    routes.emplace("/authCheck", makeRoute(new AuthCheck(context)));
    routes.emplace("/getChatList", makeRoute(new GetChatList(context)));
    routes.emplace("/getChatMessages", makeRoute(new GetChatMessages(context)));
    routes.emplace("/getNewMessages", makeRoute(new GetNewMessages(context)));
    routes.emplace("/getOwnPosts", makeRoute(new GetOwnPosts(context)));
    routes.emplace("/getUserList", makeRoute(new GetUserList(context)));
    routes.emplace("/sendMessage", makeRoute(new SendMessageRoute(context)));
    routes.emplace("/postSend", makeRoute(new UploadPost(context)));
    routes.emplace("/register", makeRoute(new RegistrationRoute(context)));
}

void    Router::route(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    auto it = routes.find(params.path());
    if (it == routes.end())
        throw std::invalid_argument("No route for requested path");
    
    std::shared_ptr<AbstractRoute> &resolver = it->second;
    resolver->resolve(req, params, session, send_);
}

std::shared_ptr<AbstractRoute>  Router::makeRoute(AbstractRoute *r)
{
    return std::shared_ptr<AbstractRoute>(r);
}
