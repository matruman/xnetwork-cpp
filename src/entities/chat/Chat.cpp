#include "Chat.hpp"

using std::move;

Chat::Chat() : isNullFlag{true}
{
}

Chat::Chat(Integer&& chatID, Integer&& userID1, Integer&& userID2, Long&& lastUsedTime)
    : chatID(move(chatID)), userID1(move(userID1)), userID2(move(userID2)), 
        lastUsedTime(move(lastUsedTime)), isNullFlag{false}
{
}
 
Chat::~Chat()
{
}

bool               Chat::isNull() const { return isNullFlag; }
const Integer&     Chat::getChatID() const { return chatID; }
const Integer&     Chat::getUserID1() const { return userID1; }
const Integer&     Chat::getUserID2() const { return userID2; }
const Long&        Chat::getLastUsedTime() const { return lastUsedTime; }
