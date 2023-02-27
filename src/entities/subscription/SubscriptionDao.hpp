#ifndef SUBSCRIPTION_DAO_HPP
#define SUBSCRIPTION_DAO_HPP

#include "Subscription.hpp"
#include <application/DBConnectionManager.hpp>
#include <SQLAPI.h>

class SubscriptionDao
{
private:
    DBConnectionManager &dbConnectionManager;
public:
    SubscriptionDao(DBConnectionManager &dcm);
    ~SubscriptionDao();
};

#endif
