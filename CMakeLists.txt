cmake_minimum_required(VERSION 3.29)
project(CPP_Template VERSION 0.1 DESCRIPTION "temp" HOMEPAGE_URL "https://github.com/flashrun24/" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)


configure_file(include/Config.h include/Config.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

message(
PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}\n
CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
)
