/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marks_reachable_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:36:16 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/25 05:42:52 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** function marks reachable nodes in a graph (farm)
*/
void				marks_reachable_nodes(t_farm *farm)
{
	t_vector		*queue;
	t_node			*u;
	t_node			*v;

	queue = ft_vnew((long)(farm->nodes->used * sizeof(void*)), sizeof(void*));
	if (queue == NULL)
		return ;
	ft_vpush_back(queue, &farm->start, sizeof(void*));
	while (QUEUE_IS_EMPTY(queue) == FALSE)
	{
		u = *(t_node**)ft_vpop_back(queue);
		MARK(u->marks);
		u->edge->items->iter = -1;
		v = *(t_node**)ft_vnext_con(u->edge->items);
		while (u->edge->items->iter < u->edge->items->head)
		{
			if (*(size_t*)v && MARKED(v->marks) == FALSE)
			{
				MARK(v->marks);
				ft_vpush_back(queue, &v, sizeof(void*));
			}
			v = *(t_node**)ft_vnext_con(u->edge->items);
		}
	}
	ft_vdel(&queue);
}
