cmake_minimum_required(VERSION 4.0)
project(PP2_Project_master C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_executable(PP2_Project_master main.c gui.c gui.h
        main.c
)

target_link_libraries(PP2_Project_master allegro allegro_main allegro_primitives allegro_font)