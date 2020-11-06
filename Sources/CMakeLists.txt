cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ioLogging)

include(FindPkgConfig)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)
 
foreach(FLAG ${LIBMYSQLCLIENT_CFLAGS_OTHER})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()
 
link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})
 
add_executable(ioLogging main.c)
target_link_libraries(ioLogging PJ_RPI)
target_include_directories(ioLogging PRIVATE ${LIBMYSQLCLIENT_INCLUDE_DIRS})
target_link_libraries(ioLogging PRIVATE ${LIBMYSQLCLIENT_LIBRARIES})

