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

User    UserDao::getById(int id)
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

User    UserDao::getByEmail(const std::string &email)
{
    SACommand command(&dbConnection, 
    _TSA("SELECT user_id, email, username, password, reg_date, last_login \
        FROM users WHERE email=:1"));
    command << SAString(email.c_str());
    command.Execute();
    if (command.FetchNext())
        return mapRequestResult(command);
    else
        return User();
}

vector<UserListElem>    UserDao::findUsers(const std::string &name, int offset)
{
    vector<UserListElem> vect;

    SACommand command(&dbConnection, 
    _TSA("SELECT u.user_id, email, username, reg_date, last_login, s1.user_id, s2.user_id FROM users u \
        LEFT JOIN subscriptions s1 ON u.user_id = s1.subscriber_id \
        LEFT JOIN subscriptions s2 ON u.user_id = s2.user_id \
        WHERE username LIKE :1 LIMIT 50 OFFSET :2"));
    std::string query = name + '%';
    command << SAString(query.c_str());
    command << (long) offset;
    command.Execute();
    while (command.FetchNext())
    {
        vect.emplace_back(
            getIntegerFromSaField(command[1]),
            getStringFromSaField(command[2]),
            getStringFromSaField(command[3]),
            getDateFromSaField(command[4]),
            getDateFromSaField(command[5]),
            command[6].isNull() ? false : true,
            command[7].isNull() ? false : true
        );
    }
    return vect;
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
