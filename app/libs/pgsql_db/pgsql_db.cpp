#ifndef pgsql_db_lib_cpp
#define pgsql_db_lib_cpp

#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "pgsql_db.h"


/**
 * @brief Класс описывающий пользователя в базе данных
 */
User User::create(pqxx::connection& dbConn, std::string username, std::string role) {
    User user;
    try {
        pqxx::work W(dbConn);
        std::string query = "INSERT INTO \"user\" (username, role) VALUES (" + W.quote(username) + ", " + W.quote(role) + ") RETURNING user_id";
        pqxx::result R = W.exec(query);
        W.commit();
        if (!R.empty()) {
            user.user_id = R[0][0].as<int>();
            user.username = username;
            user.role = role;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return user;
}

/**
 * @brief Функция для получения пользователя по его идентификатору
 */
User User::getUserById(pqxx::connection& dbConn, int id) {
    User user;
    std::cout << "getUserById" << std::endl;
    try {
        std::cout << "getUserById 1" << std::endl;
        if (dbConn.is_open()) {
            std::cout << "Connected to database successfully: " << dbConn.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
        }
        pqxx::work W(dbConn);
        std::cout << "getUserById 2" << std::endl;
        std::string query = "SELECT user_id, username, role FROM \"user\" WHERE user_id = " + W.quote(id);
        pqxx::result R = W.exec(query);
        std::cout << "getUserById 3" << std::endl;
        
        if (!R.empty()) {
            user.user_id = R[0][0].as<int>();
            user.username = R[0][1].as<std::string>();
            user.role = R[0][2].as<std::string>();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return user;
}



//     std::string username;
//     std::string role;

//     // Assume dbConn is a globally accessible pqxx::connection object

//     // Function to insert a new user into the database
//     void create(pqxx::connection& dbConn) {
//         try {
//             pqxx::work W(dbConn);
//             std::string query = "INSERT INTO \"user\" (username, role) VALUES (" + W.quote(username) + ", " + W.quote(role) + ") RETURNING user_id";
//             pqxx::result R = W.exec(query);
//             W.commit();
//             if (!R.empty()) {
//                 user_id = R[0][0].as<int>();
//             }
//         } catch (const std::exception& e) {
//             std::cerr << e.what() << std::endl;
//         }
//     }

//     // Static function to fetch a user by user_id
//     static User getUserById(pqxx::connection& dbConn, int id) {
//         User user;
//         try {
//             pqxx::work W(dbConn);
//             std::string query = "SELECT user_id, username, role FROM \"user\" WHERE user_id = " + W.quote(id);
//             pqxx::result R = W.exec(query);
            
//             if (!R.empty()) {
//                 user.user_id = R[0][0].as<int>();
//                 user.username = R[0][1].as<std::string>();
//                 user.role = R[0][2].as<std::string>();
//             }
//         } catch (const std::exception& e) {
//             std::cerr << e.what() << std::endl;
//         }
//         return user;
//     }

//     // Functions for update, delete, etc. would be similar
// };

/**
 * @brief  Класс описывающий видео в базе данных
 * 
 */
class Video {
public:
    int video_id;
    std::string hash;
    std::string filename;
    std::string description;
    int user_id;


    /**
     * @brief  Создает новую запись в таблице video
     * 
     * @param dbConn - соединение с базой данных
     */
    void create(pqxx::connection& dbConn) {
        try {
            pqxx::work W(dbConn);
            std::string query = "INSERT INTO video (hash, filename, description, user_id) VALUES (" + W.quote(hash) + ", " + W.quote(filename) + ", " + W.quote(description) + ", " + W.quote(user_id) + ") RETURNING video_id";
            pqxx::result R = W.exec(query);
            W.commit();
            if (!R.empty()) {
                video_id = R[0][0].as<int>();
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * @brief  Получает видео по его идентификатору
     * 
     * @param dbConn - соединение с базой данных
     * @param id - идентификатор видео
     * @return Video - объект видео
     */
    static Video getVideoById(pqxx::connection& dbConn, int id) {
        Video video;
        try {
            pqxx::work W(dbConn);
            std::string query = "SELECT video_id, hash, filename, description, user_id FROM video WHERE video_id = " + W.quote(id);
            pqxx::result R = W.exec(query);
            
            if (!R.empty()) {
                video.video_id = R[0][0].as<int>();
                video.hash = R[0][1].as<std::string>();
                video.filename = R[0][2].as<std::string>();
                video.description = R[0][3].as<std::string>();
                video.user_id = R[0][4].as<int>();
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        return video;
    }

    // Functions for update, delete, etc. would be similar
};
#endif