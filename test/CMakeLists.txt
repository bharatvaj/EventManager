add_executable(em_test EventManager_test.cpp)
target_link_libraries(em_test PRIVATE EventManager)

add_executable(em_custom_params em_custom_params.cpp)
target_link_libraries(em_custom_params PRIVATE EventManager)

add_test(em_callback_test em_test)
add_test(em_custom_params_test PRIVATE em_custom_params)
