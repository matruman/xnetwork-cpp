#ifndef REGISTRATION_ROUTE_HPP
#define REGISTRATION_ROUTE_HPP

#include "AbstractRoute.hpp"

class RegistrationRoute : public AbstractRoute
{
private:
    /* data */
public:
    RegistrationRoute(ApplicationContext &context);
    ~RegistrationRoute();

    void resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif
