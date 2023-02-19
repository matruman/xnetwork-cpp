#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <datatypes/datatypes.hpp>

class UserSession
{
private:
    Integer userID;
    bool isNullFlag;
public:
    UserSession();
    UserSession(const Integer& userID);
    ~UserSession();

    bool    isNull() const;
    const   Integer& getUserID() const;
};

#endif