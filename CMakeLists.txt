cmake_minimum_required(VERSION 3.0)

project(lem_in)

#set(GCC_FLAGS "-Wall -Werror -Wextra")
#gcc src/main.c src/read_stdin.c -I./inc/ -I./c/includes c/c.a -o t

file(GLOB SRC_LEMIN "src/*.c")

add_subdirectory(libft)
#add_definitions(${GCC_FLAGS})
add_executable(lem_in ${SRC_LEMIN})

target_include_directories(lem_in PUBLIC inc)
target_link_libraries(lem_in PRIVATE ft)
