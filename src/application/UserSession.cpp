#include <server/websocket_session.hpp>
#include "UserSession.hpp"
#include <iostream>

UserSession::UserSession() : 
    wsSession(nullptr), isNullFlag{true} 
{
}

UserSession::UserSession(const Integer& userID) : 
    userID(userID), wsSession(nullptr), isNullFlag{false}
{
}

UserSession::~UserSession()
{
}

bool    UserSession::isNull() const { return isNullFlag; }
const   Integer& UserSession::getUserID() const { return userID; }

void    UserSession::setWsSession(std::shared_ptr<websocket_session> wss)
{
    wsSession = wss;
}

void    UserSession::sendMessage(std::string message)
{
    if (wsSession.get() == nullptr)
        return;
    wsSession->send_message(message);
}
