#ifndef DB_CONNECTION_MANAGER_HPP
#define DB_CONNECTION_MANAGER_HPP

#include <SQLAPI.h>
#include <unordered_map>
#include <memory>
#include <thread>
#include <string>

#define DB_NAME "xnetwork" 
#define DB_USER "root"
#define DB_PASSWORD "12345678"

class DBConnectionManager
{
private:
    std::unordered_map<size_t, std::unique_ptr<SAConnection>> connections;
public:
    DBConnectionManager();
    ~DBConnectionManager();

    SAConnection*   getConnection();
};

#endif
