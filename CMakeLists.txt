cmake_minimum_required(VERSION 3.20)
project(gbemu CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(gbemu src/main.cpp)

if(TARGET SDL2::SDL2main)
    target_link_libraries(gbemu PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(gbemu PRIVATE SDL2::SDL2)

target_compile_options(gbemu PRIVATE -Wall -Wextra)