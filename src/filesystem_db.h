#ifndef filesystem_db_lib
#define filesystem_db_lib
#include <string>
#include <iostream>
#if __has_include(<std::filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif
#include <fstream>

struct filesystem_database {
    static std::string set_name(long chat_id, std::string name) {std::cerr << "Method not set"; return name;}
    static bool does_exist(long chat_id);   
    static std::string get_name(long chat_id);
    static std::string get_token();
};

#endif