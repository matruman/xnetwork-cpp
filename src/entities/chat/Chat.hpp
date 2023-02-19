#ifndef CHAT_HPP
#define CHAT_HPP

#include <datatypes/datatypes.hpp>
#include <boost/json.hpp>

namespace json = boost::json;

class Chat
{
private:
    Integer chatID;
    Integer userID1;
    Integer userID2;
    String userName1;
    String userName2;
    Long lastUsedTime;
    bool isNullFlag;

public:
    Chat();
    Chat(Integer&& chatID, Integer&& userID1, Integer&& userID2, 
            String&& userName1, String&& userName2, Long&& lastUsedTime);
    ~Chat();

    bool                isNull() const;
    const Integer&      getChatID() const;
    const Integer&      getUserID1() const;
    const Integer&      getUserID2() const;
    const String&       getUserName1() const;
    const String&       getUserName2() const;
    const Long&         getLastUsedTime() const;

    json::object        getJsonObject() const;
    
};

#endif