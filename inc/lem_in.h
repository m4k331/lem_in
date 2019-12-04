/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:55:17 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 17:10:06 by ahugh            ###   ########.fr       */
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


typedef struct		s_farm
{
	int64_t			ants;
	t_dict			*nodes;
	t_node			*start;
	t_node			*end;
	int8_t			direct;
}					t_farm;

void				process_supplied_options(uint8_t *opts, int ac, char **av);

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

#endif
