#include "utils.hpp"
#include "ApplicationContext.hpp"

void ApplicationContext::init()
{
    try {
        dbConnection.Connect(_TSA(DB_NAME), _TSA(DB_USER), _TSA(DB_PASSWORD), SA_MySQL_Client);
        std::cout << "Connected to DB" << std::endl;
    }
    catch(SAException &ex) {
        dbConnection.Rollback();
        std::cout << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}

ApplicationContext::ApplicationContext() : userDao((init(), dbConnection)), messageDao(dbConnection),
    chatDao(dbConnection)
{
}

ApplicationContext::~ApplicationContext() 
{
}

SessionManager& ApplicationContext::getSessionManager() { return sessionManager; }

UserDao&        ApplicationContext::getUserDao() { return userDao; }
MessageDao&     ApplicationContext::getMessageDao() { return messageDao; }
ChatDao&        ApplicationContext::getChatDao() { return chatDao; }
