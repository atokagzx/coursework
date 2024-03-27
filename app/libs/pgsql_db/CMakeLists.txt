add_library(pgsql_db 
        pgsql_db.h
        pgsql_db.cpp
)
target_include_directories(pgsql_db PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
