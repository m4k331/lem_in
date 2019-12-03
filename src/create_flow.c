/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:45:20 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 22:46:27 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_flow				*create_flow(void)
{
	t_flow			*flow;

	flow = (t_flow*)malloc(sizeof(t_flow));
	if (flow == NULL)
		return (NULL);
	flow->paths = ft_vnew(INITIAL_FLOWS * sizeof(void*), sizeof(void*));
	if (flow->paths == NULL)
	{
		ft_memdel((void**)&flow);
		return (NULL);
	}
	flow->steps = -1;
	return (flow);
}
