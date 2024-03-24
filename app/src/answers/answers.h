#ifndef answers_h
#define answers_h

#include <string>
#include <tgbot/tgbot.h>
#include "filesystem_db.h"
#include "pqxx/pqxx"

#define MAX_SIZE 20480 // 20 kBytes
#define MAX_DURATION 30 // 30 seconds
struct process_msgs
{   
    static void command_start(TgBot::Bot &bot, TgBot::Message::Ptr &message);
    static void set_name(TgBot::Bot &bot, TgBot::Message::Ptr &message);
    static void received_video(TgBot::Bot &bot, TgBot::Message::Ptr &message);
    static void on_video_reply(TgBot::Bot &bot, TgBot::Message::Ptr &message);
};

#endif