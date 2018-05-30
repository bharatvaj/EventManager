cmake_minimum_required(VERSION 3.0)

project(EventManager VERSION 0.1)

add_executable(EventManager test/EventManager_test.cpp )
target_include_directories(EventManager PRIVATE include)
