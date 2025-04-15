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
        sqlite3.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
