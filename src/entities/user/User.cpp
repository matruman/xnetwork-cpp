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
