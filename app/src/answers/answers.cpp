#ifndef answers_cpp
#define answers_cpp
#include <answers.h>
#include "pqxx/pqxx"
#include <iostream>
#include "pgsql_db.h"

// std::string process_msgs::db_conninfo;
// pqxx::connection process_msgs::dbConn;

/**
 * @brief Вычисляет хеш видеофайла.
 * @param bot - объект бота
 * @param video - видеофайл
 * @return uint32_t - хеш видеофайла
 */
uint32_t calculate_hash(TgBot::Bot &bot, std::shared_ptr<TgBot::Video> &video) {
    // Not developed yet.
    // Just returns video size
    return bot.getApi().getFile(video->fileId)->fileSize * video->duration;
}

/**
 * @brief Обрабатывает сообщения, не являющиеся командами.
 * @param bot - объект бота
 * @param message - сообщение
 */
void process_msgs::command_start(TgBot::Bot &bot, TgBot::Message::Ptr &message) {
    long id = message->chat->id;
    bool does_exist = filesystem_database::does_user_exist(id);
    // pqxx::connection connection(db_conninfo);
    // User user = User::getUserById(connection, id);
    printf("\x1B[34mCommand [start]:\n\t\x1B[33mid: %ld\n\texist: %s\x1B[0m\n", id, (does_exist ? "true" : "false"));
    bot.getApi().sendMessage(message->chat->id, does_exist ? "Мы уже знакомы, тебя зовут " + filesystem_database::get_name(id) + ". Если  хочешь представиться иначе, напиши </setname [Имя]>": "Как тебя зовут? Используй команду </setname [Имя]> чтобы представиться");
}

/**
 * @brief Обрабатывает команду setname.
 * @param bot - объект бота
 * @param message - сообщение
 */
void process_msgs::set_name(TgBot::Bot &bot, TgBot::Message::Ptr &message) {
    std::string name = message->text.substr(8);
    if (name.length() <= 1) {
        printf("\x1B[34mCommand [setname]:\n\t\x1B[33mempty name\x1B[0m\n");
        bot.getApi().sendMessage(message->chat->id, "Ошибка! Имя не может быть пустым", true, message->messageId);
    } else {
        name = name.substr(1);
        filesystem_database::set_name(message->chat->id, name);
        printf("\x1B[34mCommand [setname]:\n\t\x1B[33mname: %s\x1B[0m\n", name.c_str());
        bot.getApi().sendMessage(message->chat->id, "Будем знакомы, " + name, false, message->messageId);
    }
}

/**
 * @brief Обрабатывает полученное видео. Сохраняет видеофайл в директории пользователя.
 * @param bot - объект бота
 * @param message - сообщение
 */
void process_msgs::received_video(TgBot::Bot &bot, TgBot::Message::Ptr &message) {
    bool user_exist = filesystem_database::does_user_exist(message->chat->id);
    std::string user_name = filesystem_database::get_name(message->chat->id);
    auto file_info = bot.getApi().getFile(message->video->fileId);
    std::string file_id = message->video->fileId;
    float file_size_kbytes = file_info->fileSize / 1024.0;
    int32_t duration = message->video->duration;
    std::string file_name = file_info->filePath;
    bool should_save = (file_size_kbytes <= MAX_SIZE) && (duration <= MAX_DURATION) && user_exist;
    uint32_t hash = calculate_hash(bot, message->video);    
    printf("\x1B[34mVideo:\x1B[33m\n\tuser name: %s\n\tfile id: %s\n\tsize: %f kBytes\n\tduration: %d sec\n\tfile path: %s\n\tshould_download: %s\n\thash: %d\x1B[0m\n", (user_exist ? user_name : "\x1B[31mnoname\x1B[33m").c_str(), file_id.c_str(), file_size_kbytes, duration, file_name.c_str(), (should_save ? "true" : "false"), hash);
    if (should_save) {
        std::ofstream out("/BOT_DB/database/" + std::to_string(message->chat->id) + "/" + std::to_string(hash) + ".mp4", std::ios::binary);
        auto downloaded = bot.getApi().downloadFile(file_info->filePath);
        out << downloaded;
        bot.getApi().sendMessage(message->chat->id, "Видео принято", false, message->messageId);
    } 
    else if (!user_exist) {
        bot.getApi().sendMessage(message->chat->id, "Как тебя зовут? Используй команду </setname [Имя]> чтобы представиться");
    }
    else {
        bot.getApi().sendMessage(message->chat->id, "Too long video ...", false, message->messageId);
    }
}

/**
 * @brief Обрабатывает ответ на видеофайл. Сохраняет описание видеофайла.
 * @param bot - объект бота
 * @param message - сообщение
 */
void process_msgs::on_video_reply(TgBot::Bot &bot, TgBot::Message::Ptr &message) {
    std::string file_id = message->replyToMessage->video->fileId;
    uint32_t hash = calculate_hash(bot, message->replyToMessage->video);
    bool video_exist = filesystem_database::does_video_exist(message->chat->id, hash);
    bool should_save = video_exist;   
    printf("\x1B[34mReply:\n\t\x1B[33mtext: %s\n\thash: %d\n\tshould save: %s\n\tfile id: %s\x1B[0m\n", message->text.c_str(), hash, (should_save ? "true" : "false"), file_id.c_str());
    if(!video_exist)
        bot.getApi().sendMessage(message->chat->id, "Ошибка! Неизвестное видео", false, message->messageId);  
    if (should_save) {
        bot.getApi().sendMessage(message->chat->id, "Описание принято", false, message->messageId);  
        filesystem_database::save_reply(message->chat->id, hash, message->text);
    }       
}
#endif