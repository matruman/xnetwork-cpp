#include "DefaultRoute.hpp"

DefaultRoute::DefaultRoute(ApplicationContext &context) : AbstractRoute(context)
{
}

void    DefaultRoute::resolve(http::request<http::string_body>& req,
                                    session::send_lambda& send_)
{
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "Welcome!";
    res.prepare_payload();
    send_(std::move(res));
}