cmake_minimum_required(VERSION 3.30)
project(Viktorina)

set(CMAKE_CXX_STANDARD 14)

add_executable(Viktorina
        README.md
        Lietotajs.h
        Speletajs.cpp
        Speletajs.h
        Redaktors.cpp
        Redaktors.h
        LietotajuParvaldnieks.cpp
        LietotajuParvaldnieks.h
        sqlite3/sqlite3.c
        bcrypt/bcrypt.cpp
        bcrypt/blowfish.cpp
        Spele.cpp 
        Spele.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
