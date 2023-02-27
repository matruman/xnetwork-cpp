#include "DBConnectionManager.hpp"
#include <stdexcept>
#include <iostream>

DBConnectionManager::DBConnectionManager()
{
}

DBConnectionManager::~DBConnectionManager()
{
}

SAConnection*   DBConnectionManager::getConnection()
{
    size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    auto it = connections.find(thread_id);
    if (it == connections.end())
    {
        SAConnection* conn = new SAConnection(); 
        try { 
            conn->Connect(_TSA(DB_NAME), _TSA(DB_USER), _TSA(DB_PASSWORD), SA_MySQL_Client);
        }
        catch(SAException &ex) {
            conn->Rollback();
            delete conn;
            throw;
        }
        connections.emplace(thread_id, conn);
        return conn;
    }
    std::cout << "Thread id: " << thread_id << std::endl;
    return connections[thread_id].get();
}