#ifndef GET_NEW_MESSAGES_HPP
#define GET_NEW_MESSAGES_HPP

#include "AbstractRoute.hpp"

class GetNewMessages : public AbstractRoute
{
public:
    GetNewMessages(ApplicationContext &context);
    ~GetNewMessages();

    void resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif