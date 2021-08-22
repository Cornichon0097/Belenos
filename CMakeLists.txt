cmake_minimum_required(VERSION 3.16.3)

project(Belenos)

# CFLAGS for gcc.
set(CMAKE_C_FLAGS "-ansi -pedantic -Wall -Wextra -Wwrite-strings -Wstrict-prototypes -Wunreachable-code -Werror -g")

add_subdirectory(lib)
add_subdirectory(test)
