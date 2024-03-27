cmake_minimum_required(VERSION 2.8.12)
project(videobot)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
find_package(PkgConfig REQUIRED)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
# pkg_check_modules(PQXX REQUIRED pqxx)
include_directories(${PQXX_INCLUDE_DIRS})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_subdirectory(libs)

add_subdirectory(src)

install(TARGETS videobot DESTINATION bin)
