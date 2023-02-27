#include <server/utils.hpp>
#include "ApplicationContext.hpp"

void ApplicationContext::init()
{
    
}

ApplicationContext::ApplicationContext() : 
    userDao(dbConnectionManager), 
    messageDao(dbConnectionManager),
    chatDao(dbConnectionManager)
{
}

ApplicationContext::~ApplicationContext() 
{
}

SessionManager& ApplicationContext::getSessionManager() { return sessionManager; }

UserDao&        ApplicationContext::getUserDao() { return userDao; }
MessageDao&     ApplicationContext::getMessageDao() { return messageDao; }
ChatDao&        ApplicationContext::getChatDao() { return chatDao; }
