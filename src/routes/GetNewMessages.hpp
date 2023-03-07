#ifndef GET_NEW_MESSAGES_HPP
#define GET_NEW_MESSAGES_HPP

#include "AbstractRoute.hpp"

class GetNewMessages : public AbstractRoute
{
public:
    GetNewMessages(std::shared_ptr<ApplicationContext> context);
    ~GetNewMessages();

    void resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif