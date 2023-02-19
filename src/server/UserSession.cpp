#include "UserSession.hpp"

UserSession::UserSession() : isNullFlag{true} {}

UserSession::UserSession(const Integer& userID) : userID(userID), isNullFlag{false}
{
}

UserSession::~UserSession()
{
}

bool    UserSession::isNull() const { return isNullFlag; }
const   Integer& UserSession::getUserID() const { return userID; }