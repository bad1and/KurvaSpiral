cmake_minimum_required(VERSION 3.29)
project(KurvaSpiral C)
set(CMAKE_C_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(KurvaSpiral main.c)
#add_executable(KurvaSpiral test.c)

target_link_libraries(KurvaSpiral ${CURSES_LIBRARIES})