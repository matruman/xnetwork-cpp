#include "SessionManager.hpp"

SessionManager::SessionManager() : generator(rd())
{
}

SessionManager::~SessionManager()
{
}

string  SessionManager::addSession(UserSession&& session)
{
    string sessionID = generateRandomString(SESSION_ID_LENGTH);
    sessions.emplace(sessionID, session);
    return getSessionString(sessionID);
}

string  SessionManager::generateRandomString(int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

string  SessionManager::getSessionString(string sessionID)
{
    string res{"SessionID="};
    res += sessionID;
    // res += "; SameSite=None; Secure";
    return res;
}

UserSession&  SessionManager::getSession(string sessionString)
{
    string sessionID = sessionString.substr(10, SESSION_ID_LENGTH);

    auto it = sessions.find(sessionID);
    if (it == sessions.end())
        return nullSession;
    return it->second;
}