/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:25:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 19:52:27 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			reset_node(void *n)
{
	t_node			*node;

	node = n;
	node->potential += node->delta;
	node->delta = INF;
	node->predecessor = NULL;
	node->marks = 0;
	return (TRUE);
}

static inline void	update_potential(t_farm *farm)
{
	ft_dictiterate(farm->nodes, reset_node);
	farm->start->delta = 0;
}

int					prnt_edge(void *e)
{
	t_edge			*edge;

	edge = (t_edge*)e;
	printf(" [%s -> f:%d w:%d] ", edge->neighbor->name->con, edge->flow, edge->weight);
	return (1);
}

int					prnt(void *n)
{
	t_node			*node;

	node = (t_node*)n;
	if (node->predecessor)
		printf("%s<-%s d:%lld p:%lld m:%d ", node->name->con, node->predecessor->name->con, node->delta, node->potential, node->marks);
	else
		printf("%s<-(null) d:%lld p:%lld m:%d ", node->name->con, node->delta, node->potential, node->marks);
	ft_dictiterate(node->edge, prnt_edge);
	printf("\n");
	return (1);
}

int8_t				build_flows(t_flows *flows, t_farm *farm)
{
	int8_t			state;

	state = SUCCESS;
	while (state == SUCCESS)
	{
		if (dijkstra(farm) == FALSE)
		{
			perror("ERROR finding the optimal path (Dijkstra)");
			return (FALSE);
		}
		if (farm->end->predecessor == NULL)
			return (TRUE);
		if (build_residual_network(farm) == FALSE)
		{
			perror("ERROR when building a residual network");
			return (FALSE);
		}
		ft_dictiterate(farm->nodes, prnt);
		if ((state = augment_flow(flows, farm)) == ERROR)
		{
			perror("ERROR flow increase");
			return (FALSE);
		}
		update_potential(farm);
	}
	if (flows->max_flow == NULL)
	{
		perror("ERROR max flow not found");
		return (FALSE);
	}
	return (TRUE);
}
