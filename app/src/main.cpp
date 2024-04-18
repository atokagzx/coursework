#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include "filesystem_db.h"
#include <stdexcept>
#include <answers.h>

std::string token;

/**
@brief жизненный цикл бота 
@detailed точка входа
*/

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    token = filesystem_database::get_token();
    printf("\x1B[34mToken: \x1B[33m%s**********%s\x1B[0m\n", token.substr(0, 18).c_str(), token.substr(28, 18).c_str());

    TgBot::Bot bot(token);
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