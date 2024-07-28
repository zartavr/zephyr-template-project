
add_library(app_drivers INTERFACE)
add_library(app::drivers ALIAS app_drivers)

add_subdirectory(led)

target_link_libraries(app_drivers INTERFACE app::drivers::led)
