#ifndef SEND_MESSAGE_ROUTE_HPP
#define SEND_MESSAGE_ROUTE_HPP

#include "AbstractRoute.hpp"

class SendMessageRoute : public AbstractRoute
{
public:
    SendMessageRoute(ApplicationContext &context);
    ~SendMessageRoute();

    void resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif