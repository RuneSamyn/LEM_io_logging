cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ioLogging)

add_executable(ioLogging main.c)

target_link_libraries(ioLogging PJ_RPI)
