#ifndef pgsql_db_lib_h
#define pgsql_db_lib_h


#include <string>
#include <iostream>
#include <stdlib.h>
#include <pqxx/pqxx>

class User {
public:
    int user_id;
    std::string username;
    std::string role;
    User() : user_id(0), username(""), role("") {}
    User(int user_id, std::string username, std::string role) : 
        user_id(user_id), username(username), role(role) {}
    static User getUserById(pqxx::connection& dbConn, int id);
    static User create(pqxx::connection& dbConn, std::string username, std::string role);
};

#endif