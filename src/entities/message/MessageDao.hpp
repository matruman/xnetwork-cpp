#ifndef MESSAGE_DAO_HPP
#define MESSAGE_DAO_HPP

#include "Message.hpp"
#include <application/DBConnectionManager.hpp>
#include <SQLAPI.h>
#include <vector>

using std::vector;

class MessageDao
{
private:
    DBConnectionManager &dbConnectionManager;

public:
    MessageDao(DBConnectionManager &dcm);
    ~MessageDao();

    Integer save(const Message &message);
    vector<Message> getFeedPosts(int userID, int offset);
    vector<Message> getUserPosts(int userID, int offset);
    vector<Message> getChatMessages(int mainUserID, 
        int converserID, int offset);
    vector<Message> getNewMessages(int mainUserID, 
        int converserID, int lastMessageID);

    Message    mapRequestResult(SACommand &command);
};

#endif