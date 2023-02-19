#include "AuthRoute.hpp"
#include <string> 

AuthRoute::AuthRoute(ApplicationContext &context) : AbstractRoute(context)
{
}

AuthRoute::~AuthRoute()
{
}

void    AuthRoute::resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    string &body = req.body();
    json::object js = json::parse(body).as_object();
    json::string email = js.at("email").as_string();
    json::string password = js.at("password").as_string();

    User user = getContext().getUserDao().getByEmail(string(email.c_str()));
    if (user.isNull())
        return send_(unauthorized("User was not found by email", req));
    
    // std::hash used just for example, it can be replaced by real cryptographic hash function
    string passwordHash = std::to_string(std::hash<string>{}(password.c_str()));
    if (passwordHash != user.getPassword().get())
        return send_(unauthorized("Password is wrong!", req));

    SessionManager &sessionManager = getContext().getSessionManager();
    UserSession usession(user.getUserID());
    string sessionString = sessionManager.addSession(std::move(usession));

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("user", user.getJsonObject());

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::set_cookie, sessionString);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}