#ifndef USER_HPP
#define USER_HPP

#include <datatypes/datatypes.hpp>
#include <boost/json.hpp>

namespace json = boost::json;

class User
{
private:
    Integer userID;
    String email;
    String username;
    String password;
    Long regDate;
    Long lastLoginTime;
    bool isNullFlag;
    
public:
    User();
    User(Integer&& userID, String &&email, 
        String &&username, String &&password, Long &&regDate, Long &&lastLoginTime);
    ~User() = default;

    const Integer& getUserID() const;
    const String& getEmail() const;
    const String& getUsername() const;
    const String& getPassword() const;
    const Long& getRegDate() const;
    const Long& getLastLoginTime() const;
    bool isNull() const;

    json::object        getJsonObject() const;
};

#endif