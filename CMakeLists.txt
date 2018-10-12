cmake_minimum_required(VERSION 3.0)

project(EventManager VERSION 0.1)
file(GLOB_RECURSE em_HDRS "include/*.hpp")

add_executable(EventManager test/EventManager_test.cpp )
target_include_directories(EventManager PRIVATE include)
target_compile_features(EventManager PRIVATE cxx_enum_forward_declarations)

install(FILES EventManagerConfig.cmake DESTINATION lib/cmake/EventManager)
install(FILES ${em_HDRS} DESTINATION include/em)
