#ifndef ABSTRACT_ROUTE_HPP
#define ABSTRACT_ROUTE_HPP

#include <application/ApplicationContext.hpp>
#include <application/UserSession.hpp>
#include <datatypes/URLParams.hpp>
#include <server/utils.hpp>
#include <server/send_lambda.hpp>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class AbstractRoute
{
private:
    std::shared_ptr<ApplicationContext> context;
public:
    AbstractRoute(std::shared_ptr<ApplicationContext> context);

    ApplicationContext& getContext();
    virtual ~AbstractRoute() = default;
    virtual void resolve(HttpRequest& req, URLParams& params,
        UserSession& session, send_lambda& send_) = 0;
};

#endif