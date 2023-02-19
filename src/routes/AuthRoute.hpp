#ifndef AUTH_ROUTE_HPP
#define AUTH_ROUTE_HPP

#include "AbstractRoute.hpp"

class AuthRoute : public AbstractRoute
{
public:
    AuthRoute(ApplicationContext &context);
    ~AuthRoute();

    void resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif