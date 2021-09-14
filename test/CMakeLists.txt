cmake_minimum_required(VERSION 3.16.3)

project(start)

# Main example.
add_executable(${PROJECT_NAME} draws.c)
target_link_libraries(${PROJECT_NAME} PUBLIC libbelenos)
