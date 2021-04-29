cmake_minimum_required(VERSION 3.19)
project(PROGA3)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROGA3 main.cpp pugixml.hpp pugixml.cpp pugiconfig.hpp parsing.cpp parsing.h stop.h DataHandler.cpp DataHandler.h)