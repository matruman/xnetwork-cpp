#ifndef MESSAGE_DAO_HPP
#define MESSAGE_DAO_HPP

#include "Message.hpp"
#include <SQLAPI.h>
#include <vector>

using std::vector;

class MessageDao
{
private:
    SAConnection &dbConnection;

public:
    MessageDao(SAConnection &dbConnection);
    ~MessageDao();

    Integer save(const Message &message);
    vector<Message> getFeedPosts(Integer &&userID);
    vector<Message> getUserPosts(Integer &&userID);
    vector<Message> getChatMessages(Integer &&mainUserID, Integer &&converserID, int offset);

    Message    mapRequestResult(SACommand &command);

};

#endif