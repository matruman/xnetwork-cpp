#ifndef CHAT_DAO_HPP
#define CHAT_DAO_HPP

#include "Chat.hpp"
#include <SQLAPI.h>
#include <vector>

using std::vector;

class ChatDao
{
private:
    SAConnection &dbConnection;
public:
    ChatDao(SAConnection &dbConnection);
    ~ChatDao();

    Integer         createChat(int userID1, int userID2);
    vector<Chat>    getChats(int userID, int offset);
    Chat            getChat(int userID1, int userID2);
    void            updateChat(int chatID);
    bool            existsChat(int userID1, int userID2);

    Chat    mapRequestResult(SACommand &command);
};

#endif
