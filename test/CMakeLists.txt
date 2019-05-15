add_executable(em_test EventManager_test.cpp)

target_link_libraries(em_test EventManager)
target_include_directories(em_test PRIVATE EventManager)

add_test(em_callback_test em_test)
enable_testing()
