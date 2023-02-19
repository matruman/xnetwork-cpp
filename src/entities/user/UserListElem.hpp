#include "User.hpp"
#include <boost/json.hpp>

namespace json = boost::json;


class UserListElem
{
private:
    User user;
    bool subscribed;
    bool inSubscribtions;
public:
    UserListElem(Integer&& userID, String &&email, String &&username, Long &&regDate, Long &&lastLoginTime, 
        bool subscribed, bool inSubscribtions);
    ~UserListElem();

    const User&     getUser() const;
    bool            isSubscribed() const;
    bool            isInSubscribtions() const;
    json::object    getJsonObject() const;

};
