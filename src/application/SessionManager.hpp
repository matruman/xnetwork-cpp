#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <random>
#include <unordered_map>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include "UserSession.hpp"

#define SESSION_ID_LENGTH 16

using   std::string;
using   std::unordered_map;
using   std::shared_ptr;


class SessionManager
{
private:
    unordered_map<string, shared_ptr<UserSession>>  sessions;
    unordered_map<int, shared_ptr<UserSession>>     sessionsByUserID;
    std::random_device                              rd;
    std::mt19937                                    generator;
    UserSession                                     nullSession;
    std::shared_timed_mutex                         mtx;

public:
    SessionManager();
    ~SessionManager();

    string          addSession(UserSession&& session);
    string          generateRandomString(int len);
    string          getSessionString(string sessionID);
    UserSession&    getSessionByCookie(string sessionString);
    UserSession&    getSessionByUserID(int userID);

};

#endif
