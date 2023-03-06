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

    // Only one thread can write to map at the moment and no one can read during the writing
    std::unique_lock<std::shared_timed_mutex> lock(mtx);
    sessions.emplace(sessionID, std::make_shared<UserSession>(std::move(session)));
    sessionsByUserID.emplace(session.getUserID(), sessions.at(sessionID));
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
    return res;
}

UserSession&  SessionManager::getSessionByCookie(string cookie)
{
    if (cookie.length() != 10 + SESSION_ID_LENGTH)
        return nullSession;

    string sessionID = cookie.substr(10, SESSION_ID_LENGTH);

    // Multiple threads can read from map concurrently if there is no writing at the moment
    std::shared_lock<std::shared_timed_mutex> lock(mtx);
    auto it = sessions.find(sessionID);
    if (it == sessions.end())
        return nullSession;
    return *it->second.get();
}

UserSession&  SessionManager::getSessionByUserID(int userID)
{
    // Multiple threads can read from map concurrently if there is no writing at the moment
    std::shared_lock<std::shared_timed_mutex> lock(mtx);
    auto it = sessionsByUserID.find(userID);
    if (it == sessionsByUserID.end())
        return nullSession;
    return *it->second.get();
}