/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_flows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:08:09 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	flows_structure_initialization(t_flows **flows)
{
	(*flows) = (t_flows*)malloc(sizeof(t_flows));
	if (*flows == NULL)
		return (FALSE);
	(*flows)->flows = ft_vnew((INITIAL_FLOWS) * sizeof(void*), sizeof(void*));
	if ((*flows)->flows == NULL)
	{
		ft_memdel((void**)flows);
		return (FALSE);
	}
	(*flows)->best_steps = INF;
	(*flows)->max_flow = NULL;
	return (TRUE);
}

t_flows					*search_flows(t_farm *farm)
{
	t_flows				*flows;

	if (flows_structure_initialization(&flows) == FALSE)
		return (NULL);
	if (farm->direct == TRUE)
	{
		if (build_direct_flow(flows, farm) == FALSE)
			destroy_flows(&flows);
	}
	else
	{
		if (build_flows(flows, farm) == FALSE)
			destroy_flows(&flows);
	}
	return (flows);
}
