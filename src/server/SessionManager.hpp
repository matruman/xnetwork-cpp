#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <random>
#include <unordered_map>
#include "UserSession.hpp"

#define SESSION_ID_LENGTH 16

using   std::string;
using   std::unordered_map;

class SessionManager
{
private:
    unordered_map<string, UserSession>  sessions;
    std::random_device rd;
    std::mt19937 generator;
    UserSession nullSession;

public:
    SessionManager();
    ~SessionManager();

    string  addSession(UserSession&& session);
    string  generateRandomString(int len);
    string  getSessionString(string sessionID);
    UserSession&  getSession(string sessionString);
};

#endif
