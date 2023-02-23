#ifndef ABSTRACT_ROUTE_HPP
#define ABSTRACT_ROUTE_HPP

#include <server/utils.hpp>
#include <iostream>
#include <vector>
#include <server/send_lambda.hpp>
#include <server/ApplicationContext.hpp>
#include <server/UserSession.hpp>

using std::string;
using std::vector;

class AbstractRoute
{
private:
    ApplicationContext &context;
public:
    AbstractRoute(ApplicationContext &context);

    ApplicationContext& getContext() const;
    virtual ~AbstractRoute() = default;
    virtual void resolve(HttpRequest& req, urls::url_view& params,
        UserSession& session, send_lambda& send_) = 0;
};

#endif