cmake_minimum_required(VERSION 3.5.1)
project(EventManager)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Set the build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_library(EventManager INTERFACE)
target_include_directories(EventManager INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)

set(EVENTMANAGER_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(EVENTMANAGER_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/EventManager/cmake")
set(EVENTMANAGER_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/EventManager")

# Install target
install(TARGETS EventManager EXPORT EventManagerTargets
  INCLUDES DESTINATION ${EVENTMANAGER_INC_INSTALL_DIR}
)

# Install headers
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION ${EVENTMANAGER_INC_INSTALL_DIR}
)

# Make cmake config files for all targets
install(EXPORT  EventManagerTargets
  DESTINATION ${EVENTMANAGER_CMAKE_CONFIG_INSTALL_DIR}
  FILE EventManagerConfig.cmake
)

# Install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
  DESTINATION ${EVENTMANAGER_ADDITIONAL_FILES_INSTALL_DIR})

endif()

if (EVENTMANAGER_TESTS)
  add_subdirectory(test)
endif()
