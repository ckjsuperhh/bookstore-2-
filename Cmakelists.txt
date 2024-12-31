cmake_minimum_required(VERSION 3.28)
project(code)

set(CMAKE_CXX_STANDARD 26)

add_executable(code main.cpp
        user.h
        DataBase.h
        book.h
        log.h
        cmd.h)
