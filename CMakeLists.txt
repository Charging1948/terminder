cmake_minimum_required(VERSION 3.24)
project(terminder C)

set(CMAKE_C_STANDARD 99)

add_executable(terminder src/main.c src/utility.c include/appointment.h include/list.h include/element.h include/utility.h include/functions.h src/functions.c)
