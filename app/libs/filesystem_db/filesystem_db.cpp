#ifndef filesystem_db_lib_cpp
#define filesystem_db_lib_cpp

#include "filesystem_db.h"
#include <sys/stat.h>

void filesystem_database::makedir(std::string dir) {
    std::system(("mkdir -p " + DB_PATH + "database/").c_str());
    std::system(("mkdir -p " + DB_PATH + "database/" + dir).c_str());
}

void filesystem_database::makedir() {std::system(("mkdir -p " + DB_PATH + "database").c_str());}

bool filesystem_database::does_user_exist(long chat_id) {
    std::string dir = DB_PATH + "database/" + std::to_string(chat_id);
    std::ifstream file;
    file.open(dir + "/!name.txt");
    bool ret = file.is_open();
    file.close();
    return ret;
}

bool filesystem_database::does_video_exist(long chat_id, uint32_t hash) {
    std::string dir = DB_PATH + "database/" + std::to_string(chat_id) + "/" + std::to_string(hash) +  ".mp4";
    std::ifstream file;
    file.open(dir);
    bool ret = file.is_open();
    file.close();
    return ret;
}

std::string filesystem_database::get_name(long chat_id) {
    std::string dir = DB_PATH + "database/" + std::to_string(chat_id);
    std::ifstream file;
    file.open(dir + "/!name.txt");
    std::string out = "";
    if(file) {
        std::getline(file, out);
        file.close();
    }
    return out;
}

void filesystem_database::set_name(long chat_id, std::string name) {
    std::string dir = DB_PATH + "database/" + std::to_string(chat_id);
    makedir(std::to_string(chat_id));
    std::ofstream file;
    file.open(dir + "/!name.txt");
    file << name;
    file.close();
}

void filesystem_database::save_reply(long chat_id, uint32_t hash, std::string &text) {
    std::string dir = DB_PATH + "database/" + std::to_string(chat_id) + "/" + std::to_string(hash) +  ".txt";
    std::ofstream file;
    file.open(dir);
    file << text;
    file.close();
}

std::string filesystem_database::get_token() {
    std::string token;
    std::ifstream f;
    std::ios_base::iostate exceptionMask = f.exceptions() | std::ios::failbit;
    f.exceptions(exceptionMask);
    try {
        f.open("/run/secrets/tg_token");
    } catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
    }
    if (f.is_open())
        f >> token;
    f.close();
    return token;
}
#endif