/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_to_farm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 01:22:51 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** inserts a node into the dictionary
** returns TRUE or FALSE depending on the success of the insert
*/

static inline int8_t	insert_node_to_farm(t_farm *farm, t_node *node)
{
	if (ft_dictget(farm->nodes, node->name->con) != NULL)
		return (FALSE);
	return (ft_dictset(farm->nodes, node->name->con, node));
}

/*
** creates a node from the raw string and returns it, otherwise return NULL
*/

static inline t_node	*get_node(t_str *raw_str, size_t len)
{
	t_node				*node;

	ft_swap64((uint64_t*)(&raw_str->len), (uint64_t*)(&len));
	*(&raw_str->con[raw_str->len]) = NULL_TERMINATE;
	node = create_node(raw_str);
	*(&raw_str->con[raw_str->len]) = SPACE;
	ft_swap64((uint64_t*)(&raw_str->len), (uint64_t*)(&len));
	return (node);
}

/*
** adds commons nodes to the farm with the creation of an additional hash node
** with the connection hash_node --> node.
** if successful, returns SUCCESS, otherwise ERROR
*/

static inline int8_t	add_common(t_farm *farm, t_node *node)
{
	t_node				*hash_node;

	hash_node = create_hash_node(node->name);
	if (hash_node == NULL)
		return (ERROR);
	if (add_edge_to_node(hash_node, node, 1) == FALSE)
	{
		destroy_node(&hash_node);
		return (ERROR);
	}
	if (insert_node_to_farm(farm, node) == FALSE)
	{
		destroy_node(&hash_node);
		return (ERROR);
	}
	if (insert_node_to_farm(farm, hash_node) == FALSE)
	{
		destroy_node(&hash_node);
		ft_dictunset(farm->nodes, node->name->con, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** adds specific nodes to the farm, namely the start and the end
** if successful, returns SUCCESS, otherwise ERROR
*/

static inline int8_t	add_special(t_farm *farm, t_node *node, uint8_t type)
{
	if ((type & MASK_START) != FALSE)
	{
		if (farm->start != NULL)
			return (ERROR);
		farm->start = node;
		node->delta = 0;
	}
	else
	{
		if (farm->end != NULL)
			return (ERROR);
		farm->end = node;
	}
	if (insert_node_to_farm(farm, node) == FALSE)
		return (ERROR);
	return (SUCCESS);
}

/*
** by the given type from the raw string creates and adds a node to the farm.
** returns values:
** SUCCESS in the case of a successful work function
** FAIL in the case that the raw string does not fit the creation of the node
** ERROR in the case of a function error
*/

int8_t					add_node_to_farm(t_farm *farm, \
										t_str *raw_str, \
										uint8_t type)
{
	t_node				*node;
	size_t				len;
	int8_t				state;

	len = get_length_node_name(raw_str);
	if (len == 0)
		return (FAIL);
	node = get_node(raw_str, len);
	if (node == NULL)
		return (ERROR);
	if ((type & MASK_COMMON) != FALSE)
		state = add_common(farm, node);
	else
		state = add_special(farm, node, type);
	if (state == ERROR)
		destroy_node(&node);
	return (state);
}
