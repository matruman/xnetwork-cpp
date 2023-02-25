#include "AuthRoute.hpp"
#include <string> 

AuthRoute::AuthRoute(ApplicationContext &context) : AbstractRoute(context)
{
}

AuthRoute::~AuthRoute()
{
}

void    AuthRoute::resolve(HttpRequest& req, URLParams& params,
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

    HttpResponse res = success_response(payload, req);
    res.set("Set-Cookie", sessionString);
    send_(std::move(res));
}