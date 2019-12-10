/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:25:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	handle_error(char *msg)
{
	perror(msg);
	return (FALSE);
}

static int				reset_node(void *n)
{
	t_node				*node;

	node = n;
	node->potential += node->delta;
	node->delta = INF;
	node->predecessor = NULL;
	node->marks = 0;
	return (TRUE);
}

static inline void		update_potential(t_farm *farm)
{
	ft_dictiterate(farm->nodes, reset_node);
	farm->start->delta = 0;
}

int8_t					build_flows(t_flows *flows, t_farm *farm)
{
	int8_t				state;

	state = SUCCESS;
	while (state == SUCCESS)
	{
		if (dijkstra(farm) == FALSE)
			return (handle_error("ERROR finding the optimal path (Dijkstra)"));
		if (farm->end->predecessor == NULL)
			return (TRUE);
		if (build_residual_network(farm) == FALSE)
			return (handle_error("ERROR when building a residual network"));
		if ((state = augment_flow(flows, farm)) == ERROR)
			return (handle_error("ERROR flow increase"));
		update_potential(farm);
	}
	if (flows->max_flow == NULL)
		return (handle_error("ERROR max flow not found"));
	return (TRUE);
}
