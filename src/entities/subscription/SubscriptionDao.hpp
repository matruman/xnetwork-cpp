#ifndef SUBSCRIPTION_DAO_HPP
#define SUBSCRIPTION_DAO_HPP

#include "Subscription.hpp"
#include <SQLAPI.h>

class SubscriptionDao
{
private:
    SAConnection &dbConnection;
public:
    SubscriptionDao(SAConnection &dbConnection);
    ~SubscriptionDao();
};

#endif
