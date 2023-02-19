#ifndef USER_DAO_HPP
#define USER_DAO_HPP

#include "User.hpp"
#include "UserListElem.hpp"
#include <SQLAPI.h>
#include <vector>

using std::vector;

class UserDao
{
private:
    SAConnection &dbConnection;
public:
    UserDao(SAConnection &dbConnection);
    ~UserDao();

    Integer                 save(const User &user);
    User                    getById(int id);
    User                    getByEmail(const std::string &email);
    vector<UserListElem>    findUsers(const std::string &name, int offset);

    User    mapRequestResult(SACommand &command);
};

#endif