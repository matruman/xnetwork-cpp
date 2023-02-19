#include "Message.hpp"

using std::move;

Message::Message() : isNullFlag(true)
{
}

Message::Message(Integer&& messageID, Integer&& senderID, 
        Integer&& receiverID, String&& senderName, String&& text, Long&& date)
    : messageID(move(messageID)), senderID(move(senderID)), receiverID(move(receiverID)),
        senderName(move(senderName)), text(move(text)), date(move(date)), isNullFlag(false)
{
}

Message::~Message()
{
}

const Integer&      Message::getMessageID() const { return messageID; }
const Integer&      Message::getSenderID() const { return senderID; }
const Integer&      Message::getReceiverID() const { return receiverID; }
const String&       Message::getSenderName() const { return senderName; }
const String&       Message::getText() const { return text; }
const Long&         Message::getDate() const { return date; }
bool                Message::isNull() const { return isNullFlag; }

json::object        Message::getJsonObject() const
{
    json::object obj;
    obj.emplace("message_id", getMessageID().get());
    obj.emplace("sender_id", getSenderID().get());
    obj.emplace("receiver_id", getReceiverID().get());
    obj.emplace("sender_name", getSenderName().get());
    obj.emplace("text", getText().get());
    obj.emplace("date", getDate().get());
    return obj;
}

