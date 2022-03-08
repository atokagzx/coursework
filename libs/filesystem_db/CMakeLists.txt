add_library(filesystem_db 
        filesystem_db.h
        filesystem_db.cpp
)
target_include_directories(filesystem_db PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
