cmake_minimum_required(VERSION 3.0)

project(lem_in)

#set(GCC_FLAGS "-Wall -Werror -Wextra")
#gcc src/main.c src/get_fd_buffer.c -I./inc/ -I./c/includes c/c.a -o t

file(GLOB SRC_LEMIN "src/*.c")

add_subdirectory(libft)
#add_definitions(${GCC_FLAGS})
add_executable(lem_in ${SRC_LEMIN} src/destroy_room.c src/calculation_of_flow_parameters.c src/process_supplied_options.c src/show_usage.c src/display_solution.c src/insert_number_inline.c src/print_steps.c src/get_colors.c)

target_include_directories(lem_in PUBLIC inc)
target_link_libraries(lem_in PRIVATE ft)
