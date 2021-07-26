cmake_minimum_required(VERSION 3.16.3)

project(examples)

add_executable(sample.out sample.c)
target_link_libraries(sample.out PUBLIC libbelenos)
