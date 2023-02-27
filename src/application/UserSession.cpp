#include "UserSession.hpp"

UserSession::UserSession() : isNullFlag{true} {}

UserSession::UserSession(const Integer& userID) : userID(userID), isNullFlag{false}
{
}

UserSession::~UserSession()
{
}

UserSession&    UserSession::operator=(const UserSession &other)
{
    userID = other.userID;
    isNullFlag = other.isNullFlag;
    return *this;
}

bool    UserSession::isNull() const { return isNullFlag; }
const   Integer& UserSession::getUserID() const { return userID; }