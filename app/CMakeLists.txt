cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr)
project(app)

target_sources(app PRIVATE src/main.cpp)

add_subdirectory(src/drivers)

target_link_libraries(app INTERFACE app::drivers)

