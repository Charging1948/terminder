cmake_minimum_required(VERSION 3.24)
project(terminder C)

set(CMAKE_C_STANDARD 11)

add_executable(terminder src/main.c include/appointment.h include/list.h include/element.h src/utility.c)
