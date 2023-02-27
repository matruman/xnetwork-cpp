#include "ChatDao.hpp"

ChatDao::ChatDao(DBConnectionManager &dcm) : dbConnectionManager(dcm)
{
}

ChatDao::~ChatDao()
{
}

Integer ChatDao::createChat(int userID1, int userID2)
{
    SACommand command(dbConnectionManager.getConnection(),
        _TSA("INSERT INTO chats (user_id1, user_id2) VALUES (:1, :2); \
                SELECT LAST_INSERT_ID()"));
    command << (long) userID1;
    command << (long) userID2;
    command.Execute();
    if (command.FetchNext())
        return getIntegerFromSaField(command[1]);
    else
        return Integer();
}

vector<Chat>    ChatDao::getChats(int userID, int offset)
{
    vector<Chat> vect;
    SACommand command(dbConnectionManager.getConnection(), 
    _TSA("SELECT chat_id, user_id1, user_id2, u1.username, u2.username, last_used_time FROM chats c \
            INNER JOIN users u1 ON c.user_id1 = u1.user_id \
            INNER JOIN users u2 ON c.user_id2 = u2.user_id \
            WHERE user_id1=:1 OR user_id2=:1 ORDER BY last_used_time DESC LIMIT 50 OFFSET :2"));
    command << (long) userID;
    command << (long) offset;
    command.Execute();
    while (command.FetchNext())
        vect.emplace_back(mapRequestResult(command));
    return vect;
}

Chat            ChatDao::getChat(int userID1, int userID2)
{
    SACommand command(dbConnectionManager.getConnection(), 
    _TSA("SELECT chat_id, user_id1, user_id2, u1.username, u2.username, last_used_time FROM chats c \
            INNER JOIN users u1 ON c.user_id1 = u1.user_id \
            INNER JOIN users u2 ON c.user_id2 = u2.user_id \
            WHERE (user_id1=:1 AND user_id2=:2) OR (user_id1=:2 AND user_id2=:1)"));
    command << (long) userID1;
    command << (long) userID2;
    command.Execute();
    if (command.FetchNext())
        return mapRequestResult(command);
    return Chat();
}

void            ChatDao::updateChat(int chatID)
{
    SACommand command(dbConnectionManager.getConnection(), 
    _TSA("UPDATE chats SET last_used_time = CURRENT_TIMESTAMP() WHERE chat_id = :1"));
    command << (long) chatID;
    command.Execute();
}

bool    ChatDao::existsChat(int userID1, int userID2)
{
    SACommand command(dbConnectionManager.getConnection(), 
    _TSA("SELECT chat_id FROM chats WHERE \
            (user_id1=:1 AND user_id2=:2) OR (user_id1=:2 AND user_id2=:1)"));
    command << (long) userID1;
    command << (long) userID2;
    command.Execute();
    if (command.FetchNext())
        return true;
    return false;
}

Chat    ChatDao::mapRequestResult(SACommand &command)
{
    return Chat(
        getIntegerFromSaField(command[1]),
        getIntegerFromSaField(command[2]),
        getIntegerFromSaField(command[3]),
        getStringFromSaField(command[4]),
        getStringFromSaField(command[5]),
        getDateFromSaField(command[6])
    );
}
