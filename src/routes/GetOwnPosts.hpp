#ifndef GET_OWN_POSTS_HPP
#define GET_OWN_POSTS_HPP

#include "AbstractRoute.hpp"

class GetOwnPosts : public AbstractRoute
{
private:
    /* data */
public:
    GetOwnPosts(ApplicationContext &context);
    ~GetOwnPosts();

    void resolve(http::request<http::string_body>& req,
                            session::send_lambda& send_) override ;
};

#endif