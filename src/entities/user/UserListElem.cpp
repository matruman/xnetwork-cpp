#include "UserListElem.hpp"

using std::move;

UserListElem::UserListElem(Integer&& userID, String &&email, String &&username, 
    Long &&regDate, Long &&lastLoginTime, bool subscribed, bool inSubscribtions) 
    : user(move(userID), move(email), move(username), String(), move(regDate), move(lastLoginTime)), 
        subscribed{subscribed}, inSubscribtions(inSubscribtions)
{
}

UserListElem::~UserListElem()
{
}

const User&     UserListElem::getUser() const { return user; }
bool            UserListElem::isSubscribed() const { return subscribed; }
bool            UserListElem::isInSubscribtions() const { return inSubscribtions; }

json::object    UserListElem::getJsonObject() const
{
    json::object obj;
    obj.emplace("user", user.getJsonObject());
    obj.emplace("is_subscribed", isSubscribed());
    obj.emplace("is_in_subscribtions", isInSubscribtions());
    return obj;
}
