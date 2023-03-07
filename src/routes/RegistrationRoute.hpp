#ifndef REGISTRATION_ROUTE_HPP
#define REGISTRATION_ROUTE_HPP

#include "AbstractRoute.hpp"

class RegistrationRoute : public AbstractRoute
{
private:
    /* data */
public:
    RegistrationRoute(std::shared_ptr<ApplicationContext> context);
    ~RegistrationRoute();

    void resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif
