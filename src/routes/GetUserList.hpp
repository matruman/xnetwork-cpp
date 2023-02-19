#ifndef GET_USER_LIST_HPP
#define GET_USER_LIST_HPP

#include "AbstractRoute.hpp"

class GetUserList : public AbstractRoute
{
public:
    GetUserList(ApplicationContext &context);
    ~GetUserList();

    void resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif
