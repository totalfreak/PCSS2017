cmake_minimum_required(VERSION 3.5)
project(PCSS2017)

#Something something everyone else here
if(UNIX OR APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
endif()

#Something something Windooze stuff here
if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic ")
endif()

set(SOURCE_FILES
        Client/client.cpp
        )

#set(SOURCE_FILES Server/Server.cpp)

configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "clientExe")
add_executable(${EXECUTABLE_NAME} Client/client.cpp Client/Dice.cpp Client/Field.cpp Client/Player.cpp Client/Player.h Client/GameManager.cpp Server/Server.cpp)

#set(SERVER_EXECUTABLE "serverExe")
#add_executable(${SERVER_EXECUTABLE} Server/Server.cpp)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    #target_link_libraries(${SERVER_EXECUTABLE} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

