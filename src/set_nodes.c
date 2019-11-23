/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 19:32:59 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define HIDE_SPACE(x)   (*(x) = NULL_TERMINATE)
#define REVEAL_SPACE(x) (*(x) = SPACE)

/*
** returns the number of characters in the node name
*/
static inline size_t	get_length_node_name(t_str *str)
{
	size_t				len;
	char				*first;
	char				*second;

	len = str->len;
	first = ft_memrchr(str->con, SPACE, len);
	if (first == NULL || ft_isnumeric_str(first + 1, FALSE) == FALSE)
		return (0);
	len = (size_t)first - (size_t)str->con;
	second = ft_memrchr(str->con, SPACE, len);
	HIDE_SPACE(first);
	if (second == NULL || ft_isnumeric_str(second + 1, FALSE) == FALSE)
	{
		REVEAL_SPACE(first);
		return (0);
	}
	REVEAL_SPACE(first);
	len = (size_t)second - (size_t)str->con;
	if (IS_FORBIDDEN_SYMBOLS(*str->con) || ft_memchr(str->con, SEP, len))
		return (0);
	return (len);
}

static inline t_node	*get_node(t_str *str, size_t len)
{
	t_node				*node;

	ft_swap64(&str->len, &len);
	HIDE_SPACE(&str->con[str->len]);
	node = create_node(str);
	REVEAL_SPACE(&str->con[str->len]);
	ft_swap64(&str->len, &len);
	return (node);
}

static inline int8_t	add_common(t_farm *farm, t_node *node)
{
	t_node				*hash_node;

	hash_node = create_hash_node(node->name);
	if (hash_node == NULL)
		return (ERROR);
	if (add_edge_to_node(hash_node, node->name, 1) == FALSE)
	{
		destroy_node(&hash_node);
		return (ERROR);
	}
	if (add_node_to_farm(farm, node) == FALSE)
	{
		destroy_node(&hash_node);
		return (ERROR);
	}
	if (add_node_to_farm(farm, hash_node) == FALSE)
	{
		destroy_node(&hash_node);
		ft_dictunset(farm->nodes, node->name->con, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

static inline int8_t	add_special(t_farm *farm, t_node *node, uint8_t type)
{
	if (add_node_to_farm(farm, node) == FALSE)
		return (ERROR);
	if (IS_START(type))
	{
		if (farm->start != NULL)
			return (ERROR);
		farm->start = node->name;
		node->delta = 0;
	}
	else
	{
		if (farm->end != NULL)
			return (ERROR);
		farm->end = node->name;
	}
	return (SUCCESS);
}

static inline int8_t	add_node(t_farm *farm, t_str *str, uint8_t specifier)
{
	t_node				*node;
	size_t				len;
	int8_t				state;

	len = get_length_node_name(str);
	if (len == 0)
		return (FAIL);
	node = get_node(str, len);
	if (node == NULL)
		return (ERROR);
	if (IS_COMMON(specifier))
		state = add_common(farm, node);
	else
		state = add_special(farm, node, specifier);
	if (state == ERROR)
		destroy_node(&node);
	return (state);
}

/*
** set_nodes - parses the buffer and creates nodes in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/
int8_t					set_nodes(t_farm *farm, t_vector *buffer)
{
	t_str				*str;
	int8_t				state;
	uint8_t				specifier;

	specifier = MASK_COMMON;
	while (TRUE)
	{
		str = *(t_str**)ft_vnext_con(buffer);
		if (str == NULL)
			return (ERROR);
		if (IS_COMMON(specifier) && STARTS_WITH_HASH(str->con))
		{
			if (ft_strcmp(CMD_START, str->con) == 0)
				specifier = MASK_START;
			else if (ft_strcmp(CMD_END, str->con) == 0)
				specifier = MASK_END;
		}
		else
		{
			state = add_node(farm, str, specifier);
			specifier = MASK_COMMON;
			if (state != SUCCESS)
				return (state);
		}
	}
}
