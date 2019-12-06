/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:48:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/06 03:06:10 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static inline void		insert_header_inline(char *line, \
											char *color, \
											long steps, \
											int number)
{
	int					n_len;
	int					s_len;

	n_len = ft_numlen(number, 10);
	s_len = ft_numlen(steps, 10);

	if (color)
	{
		ft_memcpy(line, color, COLOR_LN);
		line += COLOR_LN;
	}
	ft_memcpy(line, HEAD_FLOW_L, HEAD_FLOW_L_LN);
	line += HEAD_FLOW_L_LN;
	line += insert_number_inline(line, number);
	ft_memcpy(line, HEAD_FLOW_M, HEAD_FLOW_M_LN);
	line += insert_number_inline(line, steps);
	ft_memcpy(line, HEAD_FLOW_R, HEAD_FLOW_R_LN);
	if (color)
	{
		ft_memcpy(line, DISCOLOR, DISCOLOR_LN);
		line += DISCOLOR_LN;
	}

}

int8_t					display_color_flow(int fd, \
											t_vector *colors, \
											t_flow *flow)
{
	char				*line;
	size_t				len = HEAD_FLOW_L_LN + n_len + HEAD_FLOW_M_LN + s_len + HEAD_FLOW_R_LN + \
			(color ? COLOR_LN + DISCOLOR_END_LN : 0);
	line
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
