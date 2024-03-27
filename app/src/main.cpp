#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include "filesystem_db.h"
// #include "pgsql_db.h\"
#include <stdexcept>
#include <answers.h>

std::string token;
std::string db_conninfo;

/**
 * @brief Получение credentials для подключения к базе данных
 * @return строка с данными для подключения к базе данных
 */
std::string get_conninfo() {
    std::string pg_user = std::getenv("POSTGRES_USER");
    std::string pg_password_file = std::getenv("POSTGRES_PASSWORD_FILE");
    std::string db_name = std::getenv("POSTGRES_DB");
    std::string pg_host = std::getenv("POSTGRES_HOST");
    std::string pg_port = std::getenv("POSTGRES_PORT");
    std::string pg_password;
    std::ifstream file(pg_password_file);
    if (file.is_open()) {
        std::getline(file, pg_password);
        file.close();
    }
    else {
        throw std::runtime_error("Can't open file with password");
    }
    return "dbname=" + db_name + " user=" + pg_user + " password=" + pg_password + " host=" + pg_host + " port=" + pg_port;
}
/**
@brief жизненный цикл бота 
@detailed точка входа
*/

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    token = filesystem_database::get_token();
    // db_conninfo = get_conninfo();
    printf("\x1B[34mToken: \x1B[33m%s**********%s\x1B[0m\n", token.substr(0, 18).c_str(), token.substr(28, 18).c_str());
    printf("\x1B[34mDB conninfo: \x1B[33m%s\x1B[0m\n", db_conninfo.c_str());

    TgBot::Bot bot(token);
    // process_msgs::db_conninfo = db_conninfo;
    // process_msgs::dbConn = pqxx::connection(db_conninfo);
    filesystem_database::makedir();
    bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message) {
            if (message->video) {
                process_msgs::received_video(bot, message);
            }
            else if (message->replyToMessage) {
                if (message->replyToMessage->video) {process_msgs::on_video_reply(bot, message);}
            }
            else {
                long id = message->chat->id;
                bool does_exist = filesystem_database::does_user_exist(id);
                bot.getApi().sendMessage(message->chat->id, does_exist ? 
                    "Чтобы добавить описание к видео, выбери контекстное меню видеоролика и используй опцию reply(ответить)" : 
                    "Используй команду </setname [Имя]> чтобы представиться");
            }
        });
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {process_msgs::command_start(bot, message);});
    bot.getEvents().onCommand("setname", [&bot](TgBot::Message::Ptr message) { process_msgs::set_name(bot, message);});
    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });
    signal(SIGABRT, [](int s) {
        printf("SIGABRT got\n");
        exit(0);
    });
    signal(SIGTERM, [](int s) {
        printf("SIGTERM got\n");
        exit(0);
    });
    
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            //printf("Long poll started\n");
            longPoll.start();
        }
    } catch (std::exception& e) {
        printf("error: %s\n", e.what());
    }
    

    return 0;
}