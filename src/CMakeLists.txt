set(Libs     
    /usr/local/lib/libTgBot.a
    ${CMAKE_THREAD_LIBS_INIT} 
    ${OPENSSL_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${CURL_LIBRARIES}
    filesystem_db
    )
include_directories(answers)
set(SOURCES answers/answers.h answers/answers.cpp)
add_executable(videobot main.cpp ${SOURCES})
target_link_libraries(videobot ${Libs})