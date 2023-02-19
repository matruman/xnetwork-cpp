#include "RegistrationRoute.hpp"

using std::string;

RegistrationRoute::RegistrationRoute(ApplicationContext &context) : AbstractRoute(context)
{
}

RegistrationRoute::~RegistrationRoute()
{
}

void    RegistrationRoute::resolve(http::request<http::string_body>& req, urls::url_view& params,
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

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = "{ \"status\" : true }";
    res.prepare_payload();
    send_(std::move(res));
}
