/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:55:17 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 01:51:37 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "node.h"
# include "flow.h"
# include <time.h>

# define INF (INT_MAX)
# define VBUFFER_SIZE 1024U
# define LEMIN_INIT_DICT_SIZE 16U
# define STARTS_WITH_HASH(str) (*(str) == '#')
# define CMD_START "##start"
# define CMD_END "##end"
# define SPACE ' '
# define SEP '-'
# define NL '\n'
# define L  'L'
# define FORBIDDEN_SYMBOLS(x) ((x) == '#' || (x) == 'L')
# define NULL_TERMINATE '\0'
# define MASK_COMMON 1U
# define MASK_START 2U
# define MASK_END 4U
# define IS_COMMON(x) ((x) & MASK_COMMON)
# define IS_START(x) ((x) & MASK_START)
# define HIDE_SYMBOL(str)      (*(str) = NULL_TERMINATE)
# define REVEAL_SYMBOL(str, s) (*(str) = (s))
# define QUEUE_IS_EMPTY(q) ((q)->iter == (q)->head - 1)
# define HEAP_IS_EMPTY(h) ((h)->n == 0)
# define NUMBER_OF_PATHS(flow) ((flow)->paths->head)
# define NUMBER_OF_ROOMS(path) ((path)->rooms->head)
# define INSERT_HASH(str) (*(str) = '#')

# define VISIT(x)        ((x) |= 2U)
# define VISITED(x)      ((x) & 2U)

# define MARK(x)         ((x) |= 1U)
# define MARKED(x)       ((x) & 1U)
# define UNMARKING(x)    ((x) ^= 1U)

# define IS_OPTION(arg) ((arg)[0] == SEP && (arg)[1] == SEP)

# define OPT_STEPS       "--steps"
# define OPT_COLOR       "--color"
# define OPT_PATHS       "--paths"
# define OPT_FLOWS       "--flows"
# define OPT_SHORT       "--short"
# define OPT_MULTI       "--multi"

# define MASK_STEPS       1U
# define MASK_COLOR       2U
# define MASK_PATHS       4U
# define MASK_FLOWS       8U
# define MASK_SHORT       16U
# define MASK_MULTI       32U
# define MASK_USAGE       128U

# define TO_STEPS(opt)    ((opt) |= MASK_STEPS)
# define TO_COLOR(opt)    ((opt) |= MASK_COLOR)
# define TO_PATHS(opt)    ((opt) |= MASK_PATHS)
# define TO_FLOWS(opt)    ((opt) |= MASK_FLOWS)
# define TO_SHORT(opt)    ((opt) |= MASK_SHORT)
# define TO_MULTI(opt)    ((opt) |= MASK_MULTI)
# define TO_USAGE(opt)    ((opt) |= MASK_USAGE)

# define IS_STEPS(opt)    ((opt) & MASK_STEPS)
# define IS_COLOR(opt)    ((opt) & MASK_COLOR)
# define IS_PATHS(opt)    ((opt) & MASK_PATHS)
# define IS_FLOWS(opt)    ((opt) & MASK_FLOWS)
# define IS_SHORT(opt)    ((opt) & MASK_SHORT)
# define IS_MULTI(opt)    ((opt) & MASK_MULTI)
# define IS_USAGE(opt)    ((opt) & MASK_USAGE)
# define IS_EMPTY(opt)    ((((opt) & 0xFD) & 0xDF) == 0)

# define MC               240
# define COLOR_CODE       "\33[38;5;000m"
# define COLOR_PREFIX_LN  7
# define FIXED_NUM_LN     3
# define DISCOLOR         "\x1b[0m"
# define DISCOLOR_LN      4
# define DISCOLOR_END     "\x1b[0m\n"
# define DISCOLOR_END_LN  5
# define NUM_MAX_LN       20
# define CODE_GOLD        220
# define CODE_PURPLE      56
# define SEP_PATH         " - "
# define SEP_PATH_LN      3
# define PATH_SHIFT_COLOR 40
# define FLOW_SHIFT_COLOR 50
# define PREFIX_PATH      "ants("
# define PREFIX_PATH_LN   5
# define SUFFIX_PATH      ") : "
# define SUFFIX_PATH_LN   4
# define HD_FLOW_L        "flow #"
# define HD_FLOW_L_LN     6
# define HD_FLOW_M        " (lines "
# define HD_FLOW_M_LN     8
# define HD_FLOW_R        "):"
# define HD_FLOW_R_LN     2
# define RM_FLOW_L        "rooms: "
# define RM_FLOW_L_LN     7
# define RM_FLOW_R        "\t|\tants: "
# define RM_FLOW_R_LN     9
# define OUT_FILE         "_out"
# define OUT_FILE_LN      4
# define MAX_FLOW_LN      (NUM_MAX_LN * 2 + HD_FLOW_L_LN + HD_FLOW_M_LN + \
									HD_FLOW_R_LN + COLOR_LN + DISCOLOR_END_LN)

# define HD_FLOW_MAIN_LN  (HD_FLOW_L_LN + HD_FLOW_M_LN + HD_FLOW_R_LN)

typedef struct		s_farm
{
	int64_t			ants;
	t_dict			*nodes;
	t_node			*start;
	t_node			*end;
	char			*file;
	int8_t			direct;
}					t_farm;

typedef struct		s_display
{
	t_vector		*colors;
	t_vector		*buffer;
	t_flows			*flows;
	t_farm			*farm;
	int				fd;
	int8_t			indent;
}					t_display;

void				display_solution(uint8_t opts, \
									t_vector *buffer, \
									t_farm *farm, \
									t_flows *flows);

void				indent_control(t_display *d);
void				print_steps(t_display *d);
int8_t				print_paths(t_display *d);
void				print_flows(t_display *d);
int8_t				print_short(t_display *d);

int8_t				display_color_path(int fd, char *color, t_path *path);
int8_t				display_path(int fd, t_path *path);

void				process_supplied_options(uint8_t *opts, int ac, char **av);
t_vector			*get_colors(int count_color);
void				show_usage(char *name_of_program);
int8_t				get_count_files(int ac, char **av);

t_farm				*build_farm(t_vector *buffer, char *file_name);
void				destroy_farm(t_farm **farm);
void				marks_reachable_nodes(t_farm *farm);
void				del_unmarked_nodes(t_farm *farm);

t_flows				*search_flows(t_farm *farm);
int8_t				build_direct_flow(t_flows *flows, t_farm *farm);
int8_t				build_flows(t_flows *flows, t_farm *farm);
int8_t				augment_flow(t_flows *flows, t_farm *farm);
void				calculation_of_flow_parameters(t_flow *flow, long ants);

int8_t				dijkstra(t_farm *farm);
int8_t				build_residual_network(t_farm *farm);
int8_t				set_ants(t_farm *farm, t_vector *buffer);
int8_t				set_nodes(t_farm *farm, t_vector *buffer);
int8_t				set_edges(t_farm *farm, t_vector *buffer);

int8_t				add_node_to_farm(t_farm *farm, \
									t_str *raw_str, \
									uint8_t type);

size_t				get_length_node_name(t_str *raw_str);
t_str				*get_hash_name(t_str *name);
t_node				*get_hash_node(t_farm *farm, t_str *name);

t_vector			*get_fd_buffer(int fd);
void				print_buffer(t_vector *buffer);
void				destroy_buffer(t_vector **buffer);

int					insert_number_inline(char *line, long num);
int8_t				convert_path_to_printable(t_path *path);
void				push_ants_one_wave(t_flow *flow, \
										t_vector *colors, \
										long *number_ant, \
										long *finished_ants);

#endif
