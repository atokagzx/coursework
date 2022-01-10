#include "filesystem_db.h"

bool filesystem_database::does_exist(long chat_id) {
    return true;
}
std::string filesystem_database::get_name(long chat_id) {
    return "Vasily, fix IT!!!";
}

std::string filesystem_database::get_token() {
    std::string token;
    std::ifstream f;
    std::ios_base::iostate exceptionMask = f.exceptions() | std::ios::failbit;
    f.exceptions(exceptionMask);
    try {
        f.open("../token.txt");
    } catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
    }
    if (f.is_open())
        f >> token;
    return token;
}