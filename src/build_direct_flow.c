/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_direct_flow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:10:04 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_path	*get_direct_path(t_farm *farm)
{
	t_path				*direct;

	direct = create_path();
	if (direct == NULL)
		return (NULL);
	ft_vpush_back(direct->rooms, &farm->start, sizeof(void*));
	ft_vpush_back(direct->rooms, &farm->end, sizeof(void*));
	direct->ants = farm->ants;
	direct->len_path = (long)(farm->start->name->len + farm->end->name->len);
	return (direct);
}

int8_t					build_direct_flow(t_flows *flows, t_farm *farm)
{
	t_flow				*flow;
	t_path				*direct_path;

	flow = create_flow();
	if (flow == NULL)
	{
		perror("ERROR creating direct flow");
		return (FALSE);
	}
	direct_path = get_direct_path(farm);
	if (direct_path == NULL)
	{
		perror("ERROR creating direct path");
		ft_memdel((void**)&flow);
		return (FALSE);
	}
	ft_vpush_back(flow->paths, &direct_path, sizeof(void*));
	flow->steps = 1;
	ft_vpush_back(flows->flows, &flow, sizeof(void*));
	flows->max_flow = flow;
	flows->best_steps = 1;
	return (TRUE);
}
