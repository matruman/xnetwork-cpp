#ifndef GET_OWN_POSTS_HPP
#define GET_OWN_POSTS_HPP

#include "AbstractRoute.hpp"

class GetOwnPosts : public AbstractRoute
{
public:
    GetOwnPosts(std::shared_ptr<ApplicationContext> context);
    ~GetOwnPosts();

    void resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif