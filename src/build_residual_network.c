/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_residual_network.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:02:51 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 19:55:57 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//def build_residual_network(self):
//u = self.farm.rooms[self.farm.end]
//while u.name != self.farm.start:
//v = self.farm.rooms[u.predecessor]
//if v.name not in u.edge:
//u.add_edge(v.name, -1)
//v.edge[u.name].flow = True
//v.edge[u.name].w = 1
//elif u.edge[v.name].w == -1:
//v.edge[u.name].flow = True
//elif u.edge[v.name].w == 1:
//u.edge[v.name].flow = False
//v.edge[u.name].w = -1
//v.edge[u.name].flow = True
//u = v
int8_t				build_residual_network(t_farm *farm)
{
	t_node			*u;
	t_node			*v;
	t_edge			*uv;
	t_edge			*vu;

	u = farm->end;
	while (u != farm->start)
	{
		v = u->predecessor;
		vu = ft_dictget(v->edge, u->name->con);
		if (ft_dictget(u->edge, v->name->con) == NULL)
		{
			if (add_edge_to_node(u, v, -1) == FALSE)
				return (FALSE);
			vu->flow = TRUE;
			vu->weight = 1;
		}
		else if ((uv = ft_dictget(u->edge, v->name->con)))
		{
			if (uv->weight == 1)
			{
				uv->flow = FALSE;
				vu->weight = -1;
			}
			vu->flow = TRUE;
		}
		else
			return (FALSE);
		u = v;
	}
	return (TRUE);
}
