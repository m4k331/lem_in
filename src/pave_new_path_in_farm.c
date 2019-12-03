/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pave_new_path_in_farm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:53:03 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 03:15:25 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	path_initialization(t_path **path, t_farm *farm)
{
	*path = create_path();
	if (*path == NULL)
		return (FALSE);
	if (ft_vpush_back((*path)->rooms, &farm->start, sizeof(void*)) == FALSE)
	{
		destroy_path(path);
		return (FALSE);
	}
	return (TRUE);
}

static inline t_node	*get_neighbor_node_with_activated_flow(t_node *u)
{
	t_node				*v;
	t_edge				*uv;

	u->edge->items->iter = -1;
	v = ft_dictnext_item(u->edge);
	while (v)
	{
		uv = ft_dictget(u->edge, v->name->con);
		if (uv && uv->flow && MARKED(v->marks) == FALSE && uv->weight == 1)
			return (v);
		v = ft_dictnext_item(u->edge);
	}
	return (NULL);
}

int8_t					pave_new_path_in_farm(t_path **path, t_farm *farm)
{
	t_node				*u;

	if (path_initialization(path, farm) == FALSE)
		return (ERROR);
	u = farm->start;
	while (u)
	{
		MARK(u->marks);
		u = get_neighbor_node_with_activated_flow(u);
		if (u && STARTS_WITH_HASH(u->name->con) == FALSE)
		{
			if (ft_vpush_back((*path)->rooms, &u, sizeof(void*)) == FALSE)
			{
				destroy_path(path);
				return (ERROR);
			}
			if (u == farm->end)
				return (SUCCESS);
		}
	}
	destroy_path(path);
	return (FAIL);
}
