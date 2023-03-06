#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <datatypes/datatypes.hpp>
#include <memory>

class websocket_session;

class UserSession
{
private:
    Integer                             userID;
    std::shared_ptr<websocket_session>  wsSession;
    bool                                isNullFlag;

public:
    UserSession();
    UserSession(const Integer& userID);
    ~UserSession();

    bool                isNull() const;
    const Integer&      getUserID() const;
    void                setWsSession(std::shared_ptr<websocket_session>  wss);
    void                sendMessage(std::string message);
};

#endif