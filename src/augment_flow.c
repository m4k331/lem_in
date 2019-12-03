/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:43:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 23:42:15 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				augment_flow(t_flows *flows, t_farm *farm)
{
	t_flow			*flow;
	t_path			*path;

	flow = create_flow();
	if (flow == NULL)
		return (ERROR);
	while (TRUE)
	{
		if (pave_new_path_in_farm(&path, farm) == ERROR)
			return (ERROR);
		if (path == NULL)
			break ;
		if (ft_vpush_back(flow->paths, &path, sizeof(void*)) == FALSE)
		{
//			destroy_flow();
//			destroy_path();
			return (ERROR);
		}
	}
//	calc_num_of_steps_in_flow(flow, farm->ants);
	if (flow->steps > 0 && flow->steps <= flows->steps)
	{
		flows->steps = flow->steps;
		if (ft_vpush_back(flows->flows, &flow, sizeof(void*)) == FALSE)
		{
//			destroy_flow();
			return (ERROR);
		}
		return (TRUE);
	}
//	destroy_flow();
	return (FALSE);
}
