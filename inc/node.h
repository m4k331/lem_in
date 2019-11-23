/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:04:55 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 16:15:19 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "edge.h"
# define MASK_MARKED 1U
# define MASK_VISITED 2U

# define IS_MARKED(x) ((x) & MASK_MARKED)
# define IS_VISITED(x) ((x) & MASK_VISITED)

typedef struct		s_node
{
	t_str			*name;
	t_str			*predecessor;
	t_dict			*edge;
	int64_t			potential;
	int64_t			delta;
	uint8_t			marks;
}					t_node;

t_node				*create_node(t_str *name);
t_node				*create_hash_node(t_str *name);
void				destroy_node(t_node **node);
t_edge				*get_node_connections(t_node *node);
int8_t				add_edge_to_node(t_node *node, t_str *neighbor, long wght);
void				del_edge_to_node(t_node *node, t_str *neighbor);
void				reset_variables_in_node(t_node *node);
int					node_cmp(void *a, void *b);

#endif
