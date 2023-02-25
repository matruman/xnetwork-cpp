#ifndef UPLOAD_POST_HPP
#define UPLOAD_POST_HPP

#include "AbstractRoute.hpp"

class UploadPost : public AbstractRoute
{
public:
    UploadPost(ApplicationContext &context);
    ~UploadPost();

    void resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_) override ;
};

#endif
