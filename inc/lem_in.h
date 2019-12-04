/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:55:17 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 21:43:54 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "node.h"
# include "flow.h"

# define INF (INT_MAX)
# define VBUFFER_SIZE 1024U
# define LEMIN_INIT_DICT_SIZE 16U
# define STARTS_WITH_HASH(str) (*(str) == '#')
# define CMD_START "##start"
# define CMD_END "##end"
# define SPACE ' '
# define SEP '-'
# define NL '\n'
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

# define VISIT(x)      ((x) |= 2U)
# define VISITED(x)    ((x) & 2U)
# define UNVISITING(x) ((x) ^= 2U)

# define MARK(x)       ((x) |= 1U)
# define MARKED(x)     ((x) & 1U)
# define UNMARKING(x)  ((x) ^= 1U)

# define OPT_STEPS     "--steps"
# define OPT_COLOR     "--color"
# define OPT_PATHS     "--paths"
# define OPT_FLOWS     "--flows"
# define OPT_SHORT     "--short"
# define OPT_MULTI     "--multi"

# define MASK_STEPS    1U
# define MASK_COLOR    2U
# define MASK_PATHS    4U
# define MASK_FLOWS    8U
# define MASK_SHORT    16U
# define MASK_MULTI    32U
# define MASK_USAGE    128U

# define TO_STEPS(opt) ((opt) |= MASK_STEPS)
# define TO_COLOR(opt) ((opt) |= MASK_COLOR)
# define TO_PATHS(opt) ((opt) |= MASK_PATHS)
# define TO_FLOWS(opt) ((opt) |= MASK_FLOWS)
# define TO_SHORT(opt) ((opt) |= MASK_SHORT)
# define TO_MULTI(opt) ((opt) |= MASK_MULTI)
# define TO_USAGE(opt) ((opt) |= MASK_USAGE)

# define IS_STEPS(opt) ((opt) & MASK_STEPS)
# define IS_COLOR(opt) ((opt) & MASK_COLOR)
# define IS_PATHS(opt) ((opt) & MASK_PATHS)
# define IS_FLOWS(opt) ((opt) & MASK_FLOWS)
# define IS_SHORT(opt) ((opt) & MASK_SHORT)
# define IS_MULTI(opt) ((opt) & MASK_MULTI)
# define IS_USAGE(opt) ((opt) & MASK_USAGE)

# define GOLD          "\33[38;5;220m"
# define PREFIX_LN     11
# define SUFFIX        "\x1b[0m"
# define SUFFIX_LN     4
# define SUFFIX_END    "\x1b[0m\n"
# define SUFFIX_END_LN 5
# define MAX_NUMBER_LN 20


typedef struct		s_farm
{
	int64_t			ants;
	t_dict			*nodes;
	t_node			*start;
	t_node			*end;
	int8_t			direct;
}					t_farm;

void				display_solution(uint8_t opts, \
									t_vector *buffer, \
									t_farm *farm, \
									t_flows *flows);

void				print_steps(t_flows *flows, int fd, int8_t color);

void				process_supplied_options(uint8_t *opts, int ac, char **av);
void				show_usage(uint8_t opts, char *name_of_program);

t_farm				*build_farm(t_vector *buffer);
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
												t_str *raw_str, uint8_t type);
size_t				get_length_node_name(t_str *raw_str);
t_str				*get_hash_name(t_str *name);
t_node				*get_hash_node(t_farm *farm, t_str *name);

t_vector			*get_fd_buffer(int fd);
void				print_buffer(t_vector *buffer);
void				destroy_buffer(t_vector **buffer);

int					insert_number_inline(char *line, long num);

#endif
