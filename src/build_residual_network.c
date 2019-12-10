/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_residual_network.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:02:51 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
			vu->weight = 1;
		}
		else if ((uv = ft_dictget(u->edge, v->name->con)) && uv->weight == 1)
		{
			uv->flow = FALSE;
			vu->weight = -1;
		}
		vu->flow = TRUE;
		u = v;
	}
	return (TRUE);
}
