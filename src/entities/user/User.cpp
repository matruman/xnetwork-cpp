#include "User.hpp"

using std::move;

User::User() : isNullFlag(true) {}

User::User(Integer&& userID, String &&email, 
    String &&username, String &&password, Long &&regDate, Long &&lastLoginTime)
    : userID(move(userID)), email(move(email)), username(move(username)), 
        password(move(password)), regDate(move(regDate)), 
        lastLoginTime(move(lastLoginTime)), isNullFlag(false) {}

const Integer& User::getUserID() const { return userID; }
const String& User::getEmail() const { return email; }
const String& User::getUsername() const { return username; }
const String& User::getPassword() const { return password; }
const Long& User::getRegDate() const { return regDate; }
const Long& User::getLastLoginTime() const { return lastLoginTime; }
bool User::isNull() const { return isNullFlag; }

json::object    User::getJsonObject() const
{
    json::object obj;
    obj.emplace("user_id", getUserID().get());
    obj.emplace("email", getEmail().get());
    obj.emplace("username", getUsername().get());
    obj.emplace("reg_date", getRegDate().get());
    if (getLastLoginTime().isNull())
        obj.emplace("last_login", nullptr);
    else
        obj.emplace("last_login", getLastLoginTime().get());
    return obj;
}