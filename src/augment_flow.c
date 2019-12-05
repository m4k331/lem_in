/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:43:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/05 02:05:05 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	path_initialization(t_path **path, t_farm *farm)
{
	*path = create_path();
	if (*path == NULL)
		return (FALSE);
	(*path)->len_path += farm->start->name->len;
	if (ft_vpush_back((*path)->rooms, &farm->start, sizeof(void*)) == FALSE)
	{
		destroy_path(path);
		return (FALSE);
	}
	return (TRUE);
}

static inline t_node	*get_neighbor_node_with_activated_flow(t_node *u)
{
	t_edge				*e;

	u->edge->items->iter = -1;
	e = ft_dictnext_item(u->edge);
	while (e)
	{
		if (e->flow && MARKED(e->neighbor->marks) == FALSE && e->weight == 1)
			return (e->neighbor);
		e = ft_dictnext_item(u->edge);
	}
	return (NULL);
}

static inline int8_t	pave_new_path_in_farm(t_path **path, t_farm *farm)
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
			(*path)->len_path += u->name->len;
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

static inline int8_t	initialize_paths_in_flow(t_flow **flow, t_farm *farm)
{
	t_path				*path;

	*flow = create_flow();
	if (*flow == NULL)
		return (FALSE);
	while (TRUE)
	{
		if (pave_new_path_in_farm(&path, farm) == ERROR)
			return (FALSE);
		if (path == NULL)
			break ;
		if (ft_vpush_back((*flow)->paths, &path, sizeof(void*)) == FALSE)
		{
			destroy_flow(flow);
			destroy_path(&path);
			return (FALSE);
		}
	}
	return (TRUE);
}

int8_t					augment_flow(t_flows *flows, t_farm *farm)
{
	t_flow				*flow;

	if (initialize_paths_in_flow(&flow, farm) == FALSE)
		return (ERROR);
	calculation_of_flow_parameters(flow, farm->ants);
	if (flow->steps > 0 && flow->steps <= flows->best_steps)
	{
		if (flow->steps < flows->best_steps)
			flows->max_flow = flow;
		flows->best_steps = flow->steps;
		if (ft_vpush_back(flows->flows, &flow, sizeof(void*)) == FALSE)
		{
			destroy_flow(&flow);
			return (ERROR);
		}
		return (SUCCESS);
	}
	destroy_flow(&flow);
	return (FAIL);
}
