/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:57:06 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/11 00:13:38 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** nodes_linker - makes connections between two nodes, according to the rule:
** in a hash node, connections go out of the usual one,
** only connections go out of the start, and only end up in the end.
** Three cases:
** 1) start --> hash_node
** 2) node --> end
** 3) node_a --> hash_node_b
**    node_b --> hash_node_a
** NOTE: connection weight is 1
*/

static inline int8_t	nodes_linker(t_farm *farm, t_node *left, t_node *right)
{
	t_node				*left_hash;
	t_node				*right_hash;
	int8_t				state;

	if (left == NULL || right == NULL || left == right)
		return (ERROR);
	left_hash = get_hash_node(farm, left->name);
	right_hash = get_hash_node(farm, right->name);
	if (left_hash == right_hash)
		state = add_edge_to_node(farm->start, farm->end, 1);
	else if (left == farm->start)
		state = add_edge_to_node(left, right_hash, 1);
	else if (right == farm->start)
		state = add_edge_to_node(right, left_hash, 1);
	else if (left == farm->end)
		state = add_edge_to_node(right, left, 1);
	else if (right == farm->end)
		state = add_edge_to_node(left, right, 1);
	else
	{
		state = add_edge_to_node(right, left_hash, 1);
		state = state && add_edge_to_node(left, right_hash, 1);
	}
	return ((state ? SUCCESS : ERROR));
}

/*
** function parses the buffer and creates connections between nodes in the farm
** returns: 0 in case of analysis completion and -1 in case of error
*/

int8_t					set_edges(t_farm *farm, t_vector *buffer)
{
	t_str				**raw;
	t_node				*left;
	t_node				*right;
	char				*sep;
	int8_t				state;

	raw = ft_vcurr_con(buffer);
	while (TRUE)
	{
		if (!STARTS_WITH_HASH((*raw)->con))
		{
			if ((sep = ft_memchr((*raw)->con, SEP, (*raw)->len)) == NULL)
				return (FAIL);
			HIDE_SYMBOL(sep);
			if ((right = ft_dictget(farm->nodes, sep + 1)) == NULL || \
				(left = ft_dictget(farm->nodes, (*raw)->con)) == NULL)
				return (ERROR);
			REVEAL_SYMBOL(sep, SEP);
			if (right != left && \
				(state = nodes_linker(farm, left, right)) != SUCCESS)
				return (state);
		}
		if ((raw = ft_vnext_con(buffer)) == NULL)
			return (ERROR);
	}
}
