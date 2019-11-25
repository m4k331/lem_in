/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marks_reachable_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:36:16 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/26 00:29:43 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** adds neighboring unlabeled nodes to the queue and marks them as added
*/
static inline void	add_unmarked_neighbors_to_queue(t_vector *queue, t_node *u)
{
	void			*edge;
	t_node			*v;

	u->edge->items->iter = -1;
	edge = ft_dictnext_item(u->edge);
	while (edge)
	{
		v = (*(t_edge**)edge)->neighbor;
		if (MARKED(v->marks) == FALSE)
		{
			MARK(v->marks);
			ft_vpush_back(queue, &v, sizeof(void*));
		}
		edge = ft_dictnext_item(u->edge);
	}
}

/*
** function marks reachable nodes in a graph (farm)
*/
void				marks_reachable_nodes(t_farm *farm)
{
	t_vector		*queue;
	t_node			*u;

	queue = ft_vnew((long)(farm->nodes->used * sizeof(void*)), sizeof(void*));
	ft_vpush_back(queue, &farm->start, sizeof(void*));
	if (queue)
	{
		while (QUEUE_IS_EMPTY(queue) == FALSE)
		{
			u = *(t_node**)ft_vnext_con(queue);
			MARK(u->marks);
			add_unmarked_neighbors_to_queue(queue, u);
		}
		ft_vdel(&queue);
	}
}
