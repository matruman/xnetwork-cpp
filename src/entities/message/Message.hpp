#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <datatypes/datatypes.hpp>
#include <boost/json.hpp>

namespace json = boost::json;

class Message
{
private:
    Integer messageID;
    Integer senderID;
    Integer receiverID;
    String senderName;
    String text;
    Long date;
    bool isNullFlag;

public:
    Message();
    Message(Integer&& messageID, Integer&& senderID, 
        Integer&& receiverID, String&& senderName, String&& text, Long&& date);
    ~Message();

    const Integer&      getMessageID() const;
    const Integer&      getSenderID() const;
    const Integer&      getReceiverID() const;
    const String&       getSenderName() const;
    const String&       getText() const;
    const Long&         getDate() const;
    bool                isNull() const;

    json::object        getJsonObject() const;

};

#endif