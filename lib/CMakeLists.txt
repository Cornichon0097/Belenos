cmake_minimum_required(VERSION 3.16.3)

project(libbelenos)

# Lib Belenos.
add_library(${PROJECT_NAME} src/frame.c src/point.c src/color.c src/draw.c src/component.c src/panel.c src/event.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC X11)
