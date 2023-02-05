#ifndef CHAT_HPP
#define CHAT_HPP

#include <datatypes/datatypes.hpp>

class Chat
{
private:
    Integer chatID;
    Integer userID1;
    Integer userID2;
    Long lastUsedTime;
    bool isNullFlag;

public:
    Chat();
    Chat(Integer&& chatID, Integer&& userID1, Integer&& userID2, Long&& lastUsedTime);
    ~Chat();

    bool                isNull() const;
    const Integer&      getChatID() const;
    const Integer&      getUserID1() const;
    const Integer&      getUserID2() const;
    const Long&         getLastUsedTime() const;

};

#endif