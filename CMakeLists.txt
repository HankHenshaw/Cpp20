cmake_minimum_required(VERSION 3.5)

project(cpp20)

add_executable(cpp main.cpp concepts.h modules.h coroutines.h others.h)

set_target_properties(cpp PROPERTIES
    CXX_STANDARD 2a
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-fcoroutines"
)

target_link_libraries(cpp
    ${CMAKE_THREAD_LIBS_INIT}
)