#include "MessageDao.hpp"

MessageDao::MessageDao(SAConnection &dbConnection) : dbConnection(dbConnection)
{
}

MessageDao::~MessageDao()
{
}

Integer MessageDao::save(const Message &message)
{
    SACommand command(&dbConnection,
        _TSA("INSERT INTO messages (sender_id, receiver_id, sender_name, text) VALUES (:1, :2, :3, :4); \
                SELECT LAST_INSERT_ID()"));
    command << (long) message.getSenderID().get();
    command << (long) message.getReceiverID().get();
    command << SAString(message.getSenderName().get().c_str());
    command << SAString(message.getText().get().c_str());
    command.Execute();
    if (command.FetchNext())
        return getIntegerFromSaField(command[1]);
    else
        return Integer();
}


vector<Message> getFeedPosts(Integer &&userID);

vector<Message> MessageDao::getUserPosts(Integer &&userID)
{
    vector<Message> vect;
    SACommand command(&dbConnection, 
    _TSA("SELECT message_id, sender_id, receiver_id, sender_name, text, date \
        FROM messages WHERE sender_id=:1 AND receiver_id=0"));
    command << (long) userID;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

vector<Message> MessageDao::getChatMessages(Integer &&mainUserID, Integer &&converserID, int offset)
{
    vector<Message> vect;
    SACommand command(&dbConnection, 
    _TSA("SELECT message_id, sender_id, receiver_id, sender_name, text, date \
        FROM messages WHERE \
        (sender_id=:1 AND receiver_id=:2) OR (sender_id=:2 AND receiver_id=:1) \
        LIMIT 50 OFFSET :3"));
    command << (long) mainUserID;
    command << (long) converserID;
    command << (long) offset;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

Message    MessageDao::mapRequestResult(SACommand &command)
{
    return Message(
        getIntegerFromSaField(command[1]),
        getIntegerFromSaField(command[2]),
        getIntegerFromSaField(command[3]),
        getStringFromSaField(command[4]),
        getStringFromSaField(command[5]),
        getDateFromSaField(command[6])
    );
}
