#include "AuthCheck.hpp"

AuthCheck::AuthCheck(ApplicationContext &context) : AbstractRoute(context)
{
}

AuthCheck::~AuthCheck()
{
}

void    AuthCheck::resolve(http::request<http::string_body>& req, urls::url_view& params,
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
    
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}