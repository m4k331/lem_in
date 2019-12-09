# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahugh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 18:51:35 by ahugh             #+#    #+#              #
#    Updated: 2019/12/09 18:01:25 by ahugh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in

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
                    run_multi_threads.c \
                    show_usage.c


# flags && compile

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -lpthread -c

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

.PHONY:				all clean fclean re

all: $(NAME)

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
	@echo $(GREEN)"cheking is norminette:"$(DGRAY)
	@norminette $(FT)/includes inc/ $(FT)/srcs $(SRC)

clean:
	@echo $(LRED)"clean!"$(DGRAY)
	make -C $(FT) clean >> /dev/null
	rm -rf $(OBJ_DIR)
	@echo $(RED)"deleted dir: "$(WHITE) $(OBJ_DIR)

fclean: clean
	@echo $(LRED)"all clean!"$(DGRAY)
	make -C $(FT) fclean >> /dev/null
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

