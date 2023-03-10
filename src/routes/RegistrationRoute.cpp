#include "RegistrationRoute.hpp"

using std::string;

RegistrationRoute::RegistrationRoute(std::shared_ptr<ApplicationContext> context) : AbstractRoute(context)
{
}

RegistrationRoute::~RegistrationRoute()
{
}

void    RegistrationRoute::resolve(HttpRequest& req, URLParams& params,
                                    UserSession& session, send_lambda& send_)
{
    string &body = req.body();
    json::object js = json::parse(body).as_object();
    json::string email = js.at("email").as_string();
    json::string username = js.at("username").as_string();
    json::string password = js.at("password").as_string();
    
    // std::hash used just for example, it can be replaced by real cryptographic hash function
    string passwordHash = std::to_string(std::hash<string>{}(password.c_str()));

    User user(0, string(email.c_str()), string(username.c_str()), passwordHash, 0, 0);
    getContext().getUserDao().save(user);

    json::object payload;
    payload.emplace("status", true);

    send_(success_response(payload, req));
}
