set(Libs     
    /usr/local/lib/libTgBot.a
    ${CMAKE_THREAD_LIBS_INIT} 
    ${OPENSSL_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${CURL_LIBRARIES}
    filesystem_db
    telebot
    )

add_executable(videobot source.cpp)
target_link_libraries(videobot ${Libs})