#ifndef AUTH_ROUTE_HPP
#define AUTH_ROUTE_HPP

#include "AbstractRoute.hpp"

class AuthRoute : public AbstractRoute
{
public:
    AuthRoute(ApplicationContext &context);
    ~AuthRoute();

    void resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif