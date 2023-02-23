#include "AuthCheck.hpp"

AuthCheck::AuthCheck(ApplicationContext &context) : AbstractRoute(context)
{
}

AuthCheck::~AuthCheck()
{
}

void    AuthCheck::resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    json::object payload;
    if (!session.isNull())
    {
        User user = getContext().getUserDao().getById(session.getUserID());
        payload.emplace("status", true);
        payload.emplace("user", user.getJsonObject());
    }
    else
        payload.emplace("status", false);
    
    send_(success_response(payload, req));
}