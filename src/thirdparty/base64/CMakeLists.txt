cmake_minimum_required(VERSION 3.5.0)

project(base64)

add_library(base64 ./base64.cpp)
target_include_directories(base64 PUBLIC ./include)
