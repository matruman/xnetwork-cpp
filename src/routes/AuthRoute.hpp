#ifndef AUTH_ROUTE_HPP
#define AUTH_ROUTE_HPP

#include "AbstractRoute.hpp"

class AuthRoute : public AbstractRoute
{
public:
    AuthRoute(std::shared_ptr<ApplicationContext> context);
    ~AuthRoute();

    void resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif