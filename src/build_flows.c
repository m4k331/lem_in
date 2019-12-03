/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:25:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 21:04:12 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				build_flows(t_flows *flows, t_farm *farm)
{
	while (TRUE)
	{
		if (dijkstra(farm) == FALSE)
		{
			perror("ERROR finding the optimal path (Dijkstra)");
			return (ERROR);
		}
		if (farm->end->predecessor == NULL)
			return (TRUE);
		if (build_residual_network(farm) == FALSE)
		{
			perror("ERROR when building a residual network");
			return (ERROR);
		}
		if (augment_flow(flows, farm) == FALSE)
			return (TRUE);
//		update_potentials(farm);
	}
}
