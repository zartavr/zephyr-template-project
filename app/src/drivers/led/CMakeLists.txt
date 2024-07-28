# Add interface inner target
add_library(app_drivers_led INTERFACE)
add_library(app::drivers::led ALIAS app_drivers_led)

target_sources(
    app_drivers_led
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/led.cpp
)

# Add sources to inner target
target_link_libraries(app_drivers_led INTERFACE app::drivers::led)
