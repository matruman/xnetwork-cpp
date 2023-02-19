#ifndef AUTH_CHECK_HPP
#define AUTH_CHECK_HPP

#include "AbstractRoute.hpp"

class AuthCheck : public AbstractRoute
{
public:
    AuthCheck(ApplicationContext &context);
    ~AuthCheck();

    void resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif