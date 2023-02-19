#ifndef GET_OWN_POSTS_HPP
#define GET_OWN_POSTS_HPP

#include "AbstractRoute.hpp"

class GetOwnPosts : public AbstractRoute
{
public:
    GetOwnPosts(ApplicationContext &context);
    ~GetOwnPosts();

    void resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif