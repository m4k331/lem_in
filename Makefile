# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 18:51:35 by ahugh             #+#    #+#              #
#    Updated: 2020/02/18 20:38:54 by rnarbo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in
VISU_NAME		=	lem-out
VISU_DIR		=	visu
VISU_BIN_DIR	=	.

# colors

BLACK			=	'\033[0;30m'
RED				=	'\033[0;31m'
GREEN			=	'\033[0;32m'
YELLOW			=	'\033[0;33m'
BLUE			=	'\033[0;34m'
MAGENTA			=	'\033[0;35m'
CYAN			=	'\033[0;36m'
GRAY			=	'\033[0;37m'

# bold color

DGRAY			=	'\033[1;30m'
LRED			=	'\033[1;31m'
LGREEN			=	'\033[1;32m'
LYELLOW			=	'\033[1;33m'
LBLUE			=	'\033[1;34m'
LMAGENTA		=	'\033[1;35m'
LCYAN			=	'\033[1;36m'
WHITE			=	'\033[1;37m'

COLOR_RESET		=	'\033[0m'

# name files

FILES			=	add_ant_to_room.c \
                    add_edge_to_node.c \
                    add_node_to_farm.c \
                    augment_flow.c \
                    build_direct_flow.c \
                    build_farm.c \
                    build_flows.c \
                    build_residual_network.c \
                    calculation_of_flow_parameters.c \
                    cmp_node.c \
                    convert_path_to_printable.c \
                    create_edge.c \
                    create_flow.c \
                    create_hash_node.c \
                    create_node.c \
                    create_path.c \
                    create_room.c \
                    del_edge.c \
                    del_unmarked_nodes.c \
                    destroy_buffer.c \
                    destroy_farm.c \
                    destroy_flow.c \
                    destroy_flows.c \
                    destroy_node.c \
                    destroy_path.c \
                    destroy_room.c \
                    dijkstra.c \
                    display_path.c \
                    display_solution.c \
                    get_colors.c \
                    get_count_files.c \
                    get_fd_buffer.c \
                    get_hash_name.c \
                    get_hash_node.c \
                    get_length_node_name.c \
                    indent_control.c \
                    insert_number_inline.c \
                    main.c \
                    marks_reachable_nodes.c \
                    print_buffer.c \
                    print_flows.c \
                    print_paths.c \
                    print_short.c \
                    print_steps.c \
                    process_supplied_options.c \
                    push_ants_one_wave.c \
                    search_flows.c \
                    set_ants.c \
                    set_edges.c \
                    set_nodes.c \
                    print_complex_path.c \
                    print_direct_path.c \
                    run.c \
                    show_usage.c


# flags && compile

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -Ofast -march=native -c

# ft library

FT				=	./libft/
FT_LIB			=	$(FT)libft.a
FT_INC			=	-I $(FT)includes/
FT_LNK			=	-L $(FT) -l ft

# dir

OBJ_DIR		=	./obj/
SRC_DIR		=	./src/
INC_DIR		=	./inc/

# all files

OBJ				=	$(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))
SRC				=	$(addprefix $(SRC_DIR), $(FILES))

# exceptions

.PHONY:				all clean fclean re visu

all: $(NAME) visu

visu:
	@echo $(COLOR_RESET)""
	make -C $(VISU_DIR) "NAME=$(VISU_NAME)" "BIN_DIR=../$(VISU_BIN_DIR)"

$(FT_LIB):
	make -C $(FT) >> /dev/null
	@echo $(GREEN)"compile libft!"$(DGRAY)

obj:
	mkdir -p $(OBJ_DIR)
	@echo $(CYAN)"create dir "$(WHITE)$(OBJ_DIR)$(DGRAY)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I. $(FT_INC) -I ./inc -o $@ -c $<
	@echo $(YELLOW)"create obj files "$(NAME)$(DGRAY)

$(NAME): obj $(FT_LIB) $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) -o $(NAME)
	@echo $(LMAGENTA)$(NAME)" - ready!"$(DGRAY)

norm:
	@echo $(GREEN)"cheking is norminette:\n"$(NAME)$(DGRAY)
	@norminette $(SRC_DIR) $(INC_DIR)
	@echo "\n"$(GREEN)$(FT)$(DGRAY)"\n"
	@make -C $(FT) norm
	@echo "\n"$(GREEN)$(VISU_DIR)$(DGRAY)"\n"
	@make -C $(VISU_DIR) norm

clean:
	@echo $(LRED)"clean!"$(DGRAY)
	make -C $(FT) clean >> /dev/null
	make -C $(VISU_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo $(RED)"deleted dir: "$(WHITE) $(OBJ_DIR)

fclean: clean
	@echo $(LRED)"all clean!"$(DGRAY)
	make -C $(FT) fclean >> /dev/null
	make -C $(VISU_DIR) clean_name "NAME=$(VISU_NAME)" "BIN_DIR=../$(VISU_BIN_DIR)"
	rm -f $(NAME)

re: fclean all

horde:
	@echo $(RED)"\n\
                                   ########                                  \n\
                               #######  ######                               \n\
                            ######         ######                            \n\
                         ######               ######                         \n\
                #####  #####                     ###### #####                \n\
               ### ######                           ##########               \n\
              ###                                           ###              \n\
              ###                                            ##              \n\
             ###                                             ###             \n\
           ####                                               ####           \n\
          ###                   #############                   ####         \n\
        ####                 ######        #####                  ####       \n\
      ####                 ####               #####                ####      \n\
    ####                 ####                   ####                 ####    \n\
   ###                  ###         #####         ###                  ###   \n\
   ###                 ###        #########        ###                 ###   \n\
    ####              ###        ###     ####       ###              ####    \n\
      ####            ###      ####        ###       ##             ###      \n\
       ####           ##      ###           ####     ##           ####       \n\
         ####         ##     ###              ##     ##          ###       # \n\
######    ####        ###    ###             ###     ##        ####    ######\n\
 #############        ###     ###           ###      ##        ##############\n\
 ###    ######         ##      ###         ###      ###        #######   ### \n\
  ###                  ###      ####     ####      ###                  ###  \n\
   ###                  ###       #### #####      ###                  ###   \n\
    ###                  ###        ######       ###                  ###    \n\
     ###                  ###                   ###                  ###     \n\
      ###     ######       ###                 ###       ######     ###      \n\
       ###############      ###               ###      ###############       \n\
                    ###      ###             ###      ####        #          \n\
                     ###      ###            ##      ###                     \n\
                      ###      ##           ###     ###                      \n\
                       ###     ###         ###     ###                       \n\
                        ##      ##         ##     ###                        \n\
                        ###     ###       ###     ##                         \n\
                         ##      ##       ###    ###                         \n\
                         ##      ##       ##     ###                         \n\
                         ###     ###     ###      #######                    \n\
                         ###     ###     ###          ###                    \n\
                    ########     ###     ###         ###                     \n\
                    #######       ##     ###         ##                      \n\
                     ##           ##     ###        ###                      \n\
                     ###         ###     ###       ###                       \n\
                      ###        ###      ##      ###                        \n\
                       ###       ##       ###    ###                         \n\
                        ###      ##        ##   ###                          \n\
                         ###     ##        ### ###                           \n\
                          ###   ###         #####                            \n\
                           ###  ##           ###                             \n\
                            ######                                           \n\
                             ####                                            \n\
"$(DGRAY)

condidat_ot_naroda:
	@echo $(BLUE) "\n\
⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣵⣿⣿⣿⠿⡟⣛⣧⣿⣯⣿⣝⡻⢿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⠋⠁⣴⣶⣿⣿⣿⣿⣿⣿⣿⣦⣍⢿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⢷⠄⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⢼⣿⣿⣿⣿\n\
⢹⣿⣿⢻⠎⠔⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿\n\
⢸⣿⣿⠇⡶⠄⣿⣿⠿⠟⡛⠛⠻⣿⡿⠿⠿⣿⣗⢣⣿⣿⣿⣿\n\
⠐⣿⣿⡿⣷⣾⣿⣿⣿⣾⣶⣶⣶⣿⣁⣔⣤⣀⣼⢲⣿⣿⣿⣿\n\
⠄⣿⣿⣿⣿⣾⣟⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⢟⣾⣿⣿⣿⣿\n\
⠄⣟⣿⣿⣿⡷⣿⣿⣿⣿⣿⣮⣽⠛⢻⣽⣿⡇⣾⣿⣿⣿⣿⣿\n\
⠄⢻⣿⣿⣿⡷⠻⢻⡻⣯⣝⢿⣟⣛⣛⣛⠝⢻⣿⣿⣿⣿⣿⣿\n\
⠄⠸⣿⣿⡟⣹⣦⠄⠋⠻⢿⣶⣶⣶⡾⠃⡂⢾⣿⣿⣿⣿⣿⣿\n\
⠄⠄⠟⠋⠄⢻⣿⣧⣲⡀⡀⠄⠉⠱⣠⣾⡇⠄⠉⠛⢿⣿⣿⣿\n\
⠄⠄⠄⠄⠄⠈⣿⣿⣿⣷⣿⣿⢾⣾⣿⣿⣇⠄⠄⠄⠄⠄⠉⠉\n\
⠄⠄⠄⠄⠄⠄⠸⣿⣿⠟⠃⠄⠄⢈⣻⣿⣿⠄⠄⠄⠄⠄⠄⠄\n\
⠄⠄⠄⠄⠄⠄⠄⢿⣿⣾⣷⡄⠄⢾⣿⣿⣿⡄⠄⠄⠄⠄⠄⡀\n\
⠄⠄⠄⠄⠄⠄⠄⠸⣿⣿⣿⠃⠄⠈⢿⣿⣿⡄⠄⠄⠄⠄⠄⠄"

obj/add_ant_to_room.o: src/add_ant_to_room.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/add_edge_to_node.o: src/add_edge_to_node.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/add_node_to_farm.o: src/add_node_to_farm.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/augment_flow.o: src/augment_flow.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/build_direct_flow.o: src/build_direct_flow.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/build_farm.o: src/build_farm.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/build_flows.o: src/build_flows.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/build_residual_network.o: src/build_residual_network.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/calculation_of_flow_parameters.o: \
  src/calculation_of_flow_parameters.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/cmp_node.o: src/cmp_node.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/convert_path_to_printable.o: src/convert_path_to_printable.c \
  inc/lem_in.h libft/includes/libft.h libft/includes/vector.h \
  libft/includes/list.h libft/includes/dlist.h libft/includes/dict.h \
  libft/includes/fib.h libft/includes/get_next_line.h \
  libft/includes/tstr.h inc/node.h inc/flow.h
obj/create_edge.o: src/create_edge.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/create_flow.o: src/create_flow.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/create_hash_node.o: src/create_hash_node.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/create_node.o: src/create_node.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/create_path.o: src/create_path.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/create_room.o: src/create_room.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/del_edge.o: src/del_edge.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/del_unmarked_nodes.o: src/del_unmarked_nodes.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_buffer.o: src/destroy_buffer.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_farm.o: src/destroy_farm.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_flow.o: src/destroy_flow.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_flows.o: src/destroy_flows.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_node.o: src/destroy_node.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_path.o: src/destroy_path.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/destroy_room.o: src/destroy_room.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/dijkstra.o: src/dijkstra.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/display_path.o: src/display_path.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/display_solution.o: src/display_solution.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_colors.o: src/get_colors.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_count_files.o: src/get_count_files.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_fd_buffer.o: src/get_fd_buffer.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_hash_name.o: src/get_hash_name.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_hash_node.o: src/get_hash_node.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/get_length_node_name.o: src/get_length_node_name.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/indent_control.o: src/indent_control.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/insert_number_inline.o: src/insert_number_inline.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/main.o: src/main.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/marks_reachable_nodes.o: src/marks_reachable_nodes.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_buffer.o: src/print_buffer.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_complex_path.o: src/print_complex_path.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_direct_path.o: src/print_direct_path.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_flows.o: src/print_flows.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_paths.o: src/print_paths.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_short.o: src/print_short.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/print_steps.o: src/print_steps.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/process_supplied_options.o: src/process_supplied_options.c \
  inc/lem_in.h libft/includes/libft.h libft/includes/vector.h \
  libft/includes/list.h libft/includes/dlist.h libft/includes/dict.h \
  libft/includes/fib.h libft/includes/get_next_line.h \
  libft/includes/tstr.h inc/node.h inc/flow.h
obj/push_ants_one_wave.o: src/push_ants_one_wave.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/run.o: src/run.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/search_flows.o: src/search_flows.c inc/lem_in.h \
  libft/includes/libft.h libft/includes/vector.h libft/includes/list.h \
  libft/includes/dlist.h libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/set_ants.o: src/set_ants.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/set_edges.o: src/set_edges.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/set_nodes.o: src/set_nodes.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
obj/show_usage.o: src/show_usage.c inc/lem_in.h libft/includes/libft.h \
  libft/includes/vector.h libft/includes/list.h libft/includes/dlist.h \
  libft/includes/dict.h libft/includes/fib.h \
  libft/includes/get_next_line.h libft/includes/tstr.h inc/node.h \
  inc/flow.h
