#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include <datatypes/datatypes.hpp>

class Subscription
{
private:
    Integer subscriptionID;
    Integer subscriberID;
    Integer userID;
    Long date;
    bool isNullFlag;

public:
    Subscription();
    Subscription(Integer &&subscriptionID, Integer &&subscriberID, Integer &&userID, Long &&date);
    ~Subscription();

    const Integer&  getSubscriptionID() const;
    const Integer&  getSubscriberID() const;
    const Integer&  getUserID() const;
    const Long&     getDate() const;

    
};

#endif