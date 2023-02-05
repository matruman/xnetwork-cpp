#include "UserDao.hpp"
#include <iostream>

UserDao::UserDao(SAConnection &dbConnection) : dbConnection(dbConnection)
{
}

UserDao::~UserDao()
{
}

Integer    UserDao::save(const User &user)
{
    SACommand command(&dbConnection, 
        _TSA("INSERT INTO users (email, username, password) VALUES (:1, :2, :3); SELECT LAST_INSERT_ID()"));
    command << SAString(user.getEmail().get().c_str());
    command << SAString(user.getUsername().get().c_str());
    command << SAString(user.getPassword().get().c_str());
    command.Execute();
    if (command.FetchNext())
        return getIntegerFromSaField(command[1]);
    else
        return Integer();
}

User    UserDao::getById(Integer id)
{
    SACommand command(&dbConnection, 
    _TSA("SELECT user_id, email, username, password, reg_date, last_login \
        FROM users WHERE user_id=:1"));
    command << (long) id;
    command.Execute();
    if (command.FetchNext())
        return mapRequestResult(command);
    else
        return User();
}

User    UserDao::mapRequestResult(SACommand &command)
{
    return User(
        getIntegerFromSaField(command[1]),
        getStringFromSaField(command[2]),
        getStringFromSaField(command[3]),
        getStringFromSaField(command[4]),
        getDateFromSaField(command[5]),
        getDateFromSaField(command[6])
    );
}
