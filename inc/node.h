/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:04:55 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/25 21:21:38 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct		s_node
{
	t_str			*name;
	struct s_node	*predecessor;
	t_dict			*edge;
	int64_t			potential;
	int64_t			delta;
	uint8_t			marks;
}					t_node;

typedef struct		s_edge
{
	t_node			*neighbor;
	int8_t			weight;
	int8_t			flow;
}					t_edge;

t_edge				*create_edge(t_node *neighbor, int8_t weight);
void				del_edge(void *edge);

t_node				*create_node(t_str *name);
t_node				*create_hash_node(t_str *name);
void				destroy_node(void *n);
t_edge				*get_node_connections(t_node *node);
int8_t				add_edge_to_node(t_node *from, t_node *to, int8_t weight);
void				del_edge_to_node(t_node *node, t_str *neighbor);
void				reset_variables_in_node(t_node *node);
int					node_cmp(void *a, void *b);
void				print_node(t_node *node);

#endif
