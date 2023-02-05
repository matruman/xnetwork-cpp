#include "Subscription.hpp"

using std::move;

Subscription::Subscription() : isNullFlag{true}
{
}

Subscription::Subscription(Integer &&subscriptionID, Integer &&subscriberID,
    Integer &&userID, Long &&date) : subscriptionID(move(subscriptionID)),
        subscriberID(move(subscriberID)), userID(move(userID)),
        date(move(date)), isNullFlag{false}
{
}

Subscription::~Subscription()
{
}

const Integer&  Subscription::getSubscriptionID() const { return subscriptionID; }
const Integer&  Subscription::getSubscriberID() const { return subscriberID; }
const Integer&  Subscription::getUserID() const { return userID; }
const Long&     Subscription::getDate() const { return date; }