#ifndef APPLICATION_CONTEXT_HPP
#define APPLICATION_CONTEXT_HPP

#include <SQLAPI.h>
#include <iostream>
#include <cstdio>

#include <entities/user/UserDao.hpp>
#include <entities/message/MessageDao.hpp>

#define DB_NAME "xnetwork" 
#define DB_USER "root"
#define DB_PASSWORD "12345678"

class ApplicationContext
{
private:
    SAConnection dbConnection;
    UserDao userDao;
    MessageDao messageDao;

public:
    void init();
    ApplicationContext();
    ~ApplicationContext();

    UserDao& getUserDao();
    MessageDao& getMessageDao();

};

#endif