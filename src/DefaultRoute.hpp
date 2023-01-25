#ifndef DEFAULT_ROUTE_HPP
#define DEFAULT_ROUTE_HPP

#include "AbstractRoute.hpp"

class DefaultRoute : public AbstractRoute
{
private:
    /* data */
public:
    DefaultRoute(/* args */) = default;
    ~DefaultRoute() = default;

    void resolve(http::request<http::string_body>& req,
                            session::send_lambda& send_) override
    {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "Welcome!";
        res.prepare_payload();
        send_(std::move(res));
    }
};

#endif