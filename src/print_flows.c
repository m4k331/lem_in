/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:48:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/05 23:32:22 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t					display_color_flow(int fd, \
											t_vector *colors, \
											t_flow *flow)
{
	char				*line;


	return (TRUE);
}

int8_t					display_flow(int fd, t_flow *flow)
{
	return (TRUE);
}

int8_t					print_flows(int fd, t_vector *colors, t_flows *flows)
{
	t_flow				**flow;

	flows->flows->iter = -1;
	flow = ft_vnext_con(flows->flows);
	if (colors)
	{
		while (flow)
		{
			if (display_color_flow(fd, colors, *flow) == FALSE)
				return (FALSE);
			flow = ft_vnext_con(flows->flows);
		}
	}
	else
	{
		while (flow)
		{
			if (display_flow(fd, *flow) == FALSE)
				return (FALSE);
			flow = ft_vnext_con(flows->flows);
		}
	}
	return (TRUE);
}
