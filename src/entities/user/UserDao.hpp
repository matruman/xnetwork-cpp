#ifndef USER_DAO_HPP
#define USER_DAO_HPP

#include "User.hpp"
#include <SQLAPI.h>

class UserDao
{
private:
    SAConnection &dbConnection;
public:
    UserDao(SAConnection &dbConnection);
    ~UserDao();

    Integer save(const User &user);
    User    getById(Integer id);
    User    getByEmail(std::string email);

    User    mapRequestResult(SACommand &command);
};

#endif