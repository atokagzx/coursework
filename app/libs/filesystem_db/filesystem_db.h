#ifndef filesystem_db_lib_h
#define filesystem_db_lib_h


#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#if __has_include(<std::filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif
const std::string DB_PATH = "/BOT_DB/";

/**
 * @brief Класс для работы с файловой системой
 */
struct filesystem_database {
    static void set_name(long chat_id, std::string name);
    static bool does_user_exist(long chat_id);   
    static bool does_video_exist(long chat_id, uint32_t hash);   
    static std::string get_name(long chat_id);
    static std::string get_token();
    static void makedir(std::string dir);
    static void makedir();
    static void save_reply(long chat_id, uint32_t hash, std::string &text);
};

#endif