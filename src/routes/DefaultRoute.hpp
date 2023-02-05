#ifndef DEFAULT_ROUTE_HPP
#define DEFAULT_ROUTE_HPP

#include "AbstractRoute.hpp"

class DefaultRoute : public AbstractRoute
{
private:
    /* data */
public:
    DefaultRoute(ApplicationContext &context);
    ~DefaultRoute() = default;

    void resolve(http::request<http::string_body>& req,
                            session::send_lambda& send_) override ;
};

#endif