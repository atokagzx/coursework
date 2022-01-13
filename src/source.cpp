#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include "filesystem_db.h"
#include <stdexcept>

int max_size = 20480; // 20 kBytes
int max_duration = 30; // 30 seconds
std::string token;

uint32_t calculate_hash(TgBot::Bot &bot, std::shared_ptr<TgBot::Video> &video) {
    // Not developed yet.
    // Just returns video size
    return bot.getApi().getFile(video->fileId)->fileSize * video->duration;
}
int main() {
    token = filesystem_database::get_token();
    printf("\x1B[34mToken: \x1B[33m%s**********%s\x1B[0m\n", token.substr(0, 18).c_str(), token.substr(28, 18).c_str());
    TgBot::Bot bot(token);
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
            /*
            if (!message->photo.empty()) {
                auto file_id = message->photo[0]->fileId;
                auto file_info = bot.getApi().getFile(message->photo[message->photo.size() - 1]->fileId);
                auto downloaded = bot.getApi().downloadFile(file_info->filePath);

                std::ofstream out(message->photo[0]->fileId + ".jpg", std::ios::binary);
                out << downloaded;
            }
            */
            if (message->video) {
                auto file_info = bot.getApi().getFile(message->video->fileId);
                std::string file_id = message->video->fileId;
                float file_size_kbytes = file_info->fileSize / 1024.0;
                int32_t duration = message->video->duration;
                std::string file_name = file_info->filePath;
                bool should_save = (file_size_kbytes <= max_size) && (duration <= max_duration);
                uint32_t hash = calculate_hash(bot, message->video);    
                printf("\x1B[34mVideo:\x1B[33m\n\tfile id: %s\n\tsize: %f kBytes\n\tduration: %d sec\n\tfile path: %s\n\tshould_download: %s\n\thash: %d\x1B[0m\n", file_id.c_str(), file_size_kbytes, duration, file_name.c_str(), (should_save ? "true" : "false"), hash);
                if (should_save) {
                    std::ofstream out(std::to_string(hash) + ".mp4", std::ios::binary);
                    auto downloaded = bot.getApi().downloadFile(file_info->filePath);
                    out << downloaded;
                } else {
                    bot.getApi().sendMessage(message->chat->id, "Too long video ...");
                }
            }
            else if (message->replyToMessage) {
                if (message->replyToMessage->video) {
                    std::string file_id = message->replyToMessage->video->fileId;
                    printf("\x1B[34mReply:\n\t\x1B[33mtext: %s\n\tfile id: %s\x1B[0m\n", message->text.c_str(), file_id.c_str());
                }
            }
        });
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        long id = message->chat->id;
        bool does_exist = filesystem_database::does_exist(id);
        printf("\x1B[34mCommand [start]:\n\t\x1B[33mid: %ld\n\texist: %s\x1B[0m\n", id, (does_exist ? "true" : "false"));
        bot.getApi().sendMessage(message->chat->id, does_exist ? "Мы уже знакомы, тебя зовут " + filesystem_database::get_name(id) + ". Если  хочешь представиться иначе, напиши </setname [Имя]>": "Как тебя зовут? Используй команду </setname [Имя]> чтобы представиться");
        // #TODO create folder with user id
    });
    bot.getEvents().onCommand("setname", [&bot](TgBot::Message::Ptr message) {
        std::string name = message->text.substr(8);
        printf("\x1B[34mCommand [setname]:\n\t\x1B[33mname: %s\x1B[0m\n", name.c_str());
        bot.getApi().sendMessage(message->chat->id, "Будем знакомы, " + name);
    });
    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
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