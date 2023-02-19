#include "Chat.hpp"

using std::move;

Chat::Chat() : isNullFlag{true}
{
}

Chat::Chat(Integer&& chatID, Integer&& userID1, Integer&& userID2,
            String&& userName1, String&& userName2, Long&& lastUsedTime)
    : chatID(move(chatID)), userID1(move(userID1)), userID2(move(userID2)), 
        userName1(move(userName1)), userName2(move(userName2)),
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
const String&      Chat::getUserName1() const { return userName1; }
const String&      Chat::getUserName2() const { return userName2; }
const Long&        Chat::getLastUsedTime() const { return lastUsedTime; }

json::object       Chat::getJsonObject() const
{
    //    "chat_id, user_id1, user_id2, username1, username2, last_used_time"
    json::object obj;
    obj.emplace("chat_id", getChatID().get());
    obj.emplace("user_id1", getUserID1().get());
    obj.emplace("user_id2", getUserID2().get());
    obj.emplace("username1", getUserName1().get());
    obj.emplace("username2", getUserName2().get());
    obj.emplace("last_used_time", getLastUsedTime().get());
    return obj;
}