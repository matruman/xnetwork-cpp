#include "MessageDao.hpp"

MessageDao::MessageDao(SAConnection &dbConnection) : dbConnection(dbConnection)
{
}

MessageDao::~MessageDao()
{
}

Integer     MessageDao::save(const Message &message)
{
    SACommand command(&dbConnection,
        _TSA("INSERT INTO messages (sender_id, receiver_id, text) VALUES (:1, :2, :3); \
                SELECT LAST_INSERT_ID()"));
    command << (long) message.getSenderID().get();
    command << (long) message.getReceiverID().get();
    command << SAString(message.getText().get().c_str());
    command.Execute();
    if (command.FetchNext())
        return getIntegerFromSaField(command[1]);
    else
        return Integer();
}


vector<Message>     getFeedPosts(const Integer &userID, int offset);

vector<Message>     MessageDao::getUserPosts(int userID, int offset)
{
    vector<Message> vect;
    SACommand command(&dbConnection, 
    _TSA("SELECT message_id, sender_id, receiver_id, u.username, text, date FROM messages m \
        INNER JOIN users u ON m.sender_id = u.user_id \
        WHERE sender_id=:1 AND receiver_id=0 ORDER BY message_id DESC LIMIT 50 OFFSET :2"));
    command << (long) userID;
    command << (long) offset;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

vector<Message>     MessageDao::getChatMessages(int mainUserID, 
        int converserID, int offset)
{
    vector<Message> vect;
    SACommand command(&dbConnection, 
    _TSA("SELECT message_id, sender_id, receiver_id, u.username, text, date FROM messages m \
        INNER JOIN users u ON m.sender_id = u.user_id \
        WHERE (sender_id=:1 AND receiver_id=:2) OR (sender_id=:2 AND receiver_id=:1) \
        ORDER BY message_id DESC LIMIT 50 OFFSET :3"));
    command << (long) mainUserID;
    command << (long) converserID;
    command << (long) offset;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

vector<Message>     MessageDao::getNewMessages(int mainUserID, 
        int converserID, int lastMessageID)
{
    vector<Message> vect;
    SACommand command(&dbConnection, 
    _TSA("SELECT message_id, sender_id, receiver_id, u.username, text, date FROM messages m \
        INNER JOIN users u ON m.sender_id = u.user_id \
        WHERE ((sender_id=:1 AND receiver_id=:2) OR (sender_id=:2 AND receiver_id=:1)) \
        AND message_id > :3 ORDER BY message_id DESC LIMIT 50"));
    command << (long) mainUserID;
    command << (long) converserID;
    command << (long) lastMessageID;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

Message     MessageDao::mapRequestResult(SACommand &command)
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
