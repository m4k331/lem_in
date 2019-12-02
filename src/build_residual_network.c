/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_residual_network.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:02:51 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 13:41:32 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				build_residual_network(t_farm *farm)
{
	t_node			*u;
	t_node			*v;
	t_edge			*vu;
	t_edge			*uv;

	u = farm->end;
	while (u != farm->start)
	{
		v = u->predecessor;
		uv = ft_dictget(u->edge, v->name->con);
		if (ft_dictget(u->edge, v->name->con) == NULL)
		{
			if (add_edge_to_node(u, v, -1) == FALSE)
				return (FALSE);
			vu = ft_dictget(v->edge, u->name->con);
			vu->flow = TRUE;
			vu->weight = 1;
		}
		else if (uv->weight == -1)
		{
			vu = ft_dictget(v->edge, u->name->con);
			vu->flow = TRUE;
		}
		else if (uv->weight == 1)
		{
			vu = ft_dictget(v->edge, u->name->con);
			uv->flow = FALSE;
			vu->flow = TRUE;
			vu->weight = -1;
		}
		u = v;
	}
	return (TRUE);
}
