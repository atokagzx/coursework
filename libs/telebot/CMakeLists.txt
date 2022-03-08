add_library(telebot 
        telebot.h
        telebot.cpp
)

target_include_directories(telebot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})