cmake_minimum_required(VERSION 3.16.3)

project(libbelenos)

# Lib Belenos.
add_library(${PROJECT_NAME} src/color.c src/draw.c src/frame.c src/point.c src/component.c src/event.c src/panel.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC X11)
