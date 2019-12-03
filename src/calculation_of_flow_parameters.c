/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_of_flow_parameters.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:14:45 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 20:53:43 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	calc_ants_for_all_paths(t_vector *paths, long ants)
{
	t_path			**target;
	t_path			**path;
	long			remainder;
	long			iter;

	paths->iter = paths->head;
	target = ft_vback_con(paths);
	while (target)
	{
		remainder = ants;
		iter = 0;
		while (iter < paths->iter)
		{
			path = ft_vat(paths, iter);
			remainder -= NUMBER_OF_ROOMS(*target) - NUMBER_OF_ROOMS(*path);
			iter++;
		}
		(*target)->ants = remainder > 0 ? remainder / (paths->iter + 1) : 0;
		ants -= (*target)->ants;
		target = ft_vback_con(paths);
	}
}

static inline void	calc_number_of_steps_in_flow(t_flow *flow, long ants)
{
	t_path			**path;
	long			sum_all_rooms;

	sum_all_rooms = 0;
	flow->paths->iter = -1;
	path = ft_vnext_con(flow->paths);
	while (path)
	{
		sum_all_rooms += NUMBER_OF_ROOMS(*path);
		path = ft_vnext_con(flow->paths);
	}
	flow->steps = (ants + sum_all_rooms) / NUMBER_OF_PATHS(flow) - 1;
}

void				calculation_of_flow_parameters(t_flow *flow, long ants)
{
	if (NUMBER_OF_PATHS(flow) > 0)
	{
		calc_number_of_steps_in_flow(flow, ants);
		calc_ants_for_all_paths(flow->paths, ants);
	}
}
