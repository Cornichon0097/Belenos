cmake_minimum_required(VERSION 3.16.3)

project(libbelenos)

add_library(${PROJECT_NAME} src/color.c  src/component.c  src/event.c  src/panel.c  src/window.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC X11)
