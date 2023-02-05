#ifndef UPLOAD_POST_HPP
#define UPLOAD_POST_HPP

#include "AbstractRoute.hpp"

class UploadPost : public AbstractRoute
{
private:
    /* data */
public:
    UploadPost(ApplicationContext &context);
    ~UploadPost();

    void resolve(http::request<http::string_body>& req,
                            session::send_lambda& send_) override ;
};

#endif
