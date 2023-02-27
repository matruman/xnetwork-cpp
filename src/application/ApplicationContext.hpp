#ifndef APPLICATION_CONTEXT_HPP
#define APPLICATION_CONTEXT_HPP

#include <SQLAPI.h>
#include <iostream>
#include <cstdio>

#include <entities/user/UserDao.hpp>
#include <entities/message/MessageDao.hpp>
#include <entities/chat/ChatDao.hpp>
#include "DBConnectionManager.hpp"
#include "SessionManager.hpp"

class ApplicationContext
{
private:
    SessionManager          sessionManager;
    DBConnectionManager     dbConnectionManager;
    UserDao                 userDao;
    MessageDao              messageDao;
    ChatDao                 chatDao;

public:
    void init();
    ApplicationContext();
    ~ApplicationContext();

    SessionManager&     getSessionManager();
    UserDao&            getUserDao();
    MessageDao&         getMessageDao();
    ChatDao&            getChatDao();
};

#endif