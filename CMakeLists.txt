cmake_minimum_required(VERSION 2.8.9)
project (hello)

add_library(date tz.cpp)
target_compile_definitions(date PUBLIC HAS_REMOTE_API=0
                                       USE_OS_TZDB=1)

find_package(Threads)
add_executable(hello main.cpp)
target_link_libraries(hello date
                            ${CMAKE_THREAD_LIBS_INIT})