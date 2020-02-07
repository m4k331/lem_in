/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:48:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void		print_header(int fd, \
									char *line, \
									char *color, \
									long steps)
{
	static int			num = 1;
	int					len;

	len = ft_numlen(num, 10) + ft_numlen(steps, 10) + 16 + \
									(color ? COLOR_LN + DISCOLOR_END_LN : 1);
	if (color)
	{
		ft_memcpy(line, color, COLOR_LN);
		line += COLOR_LN;
	}
	ft_memcpy(line, HD_FLOW_L, HD_FLOW_L_LN);
	line += HD_FLOW_L_LN;
	line += insert_number_inline(line, num++);
	ft_memcpy(line, HD_FLOW_M, HD_FLOW_M_LN);
	line += HD_FLOW_M_LN;
	line += insert_number_inline(line, steps);
	ft_memcpy(line, HD_FLOW_R, HD_FLOW_R_LN);
	line += HD_FLOW_R_LN;
	if (color)
	{
		ft_memcpy(line, DISCOLOR, DISCOLOR_LN);
		line += DISCOLOR_LN;
	}
	*line = NL;
	write(fd, line - len + 1, len);
}

static inline void		print_path(int fd, \
									char *line, \
									char *color, \
									t_path *path)
{
	int					len;

	len = RM_FLOW_L_LN + RM_FLOW_R_LN + \
		ft_numlen(path->rooms->head, 10) + ft_numlen(path->ants, 10) + \
		(color ? COLOR_LN + DISCOLOR_END_LN : 1);
	if (color)
	{
		ft_memcpy(line, color, COLOR_LN);
		line += COLOR_LN;
	}
	ft_memcpy(line, RM_FLOW_L, RM_FLOW_L_LN);
	line += RM_FLOW_L_LN;
	line += insert_number_inline(line, path->rooms->head);
	ft_memcpy(line, RM_FLOW_R, RM_FLOW_R_LN);
	line += RM_FLOW_R_LN;
	line += insert_number_inline(line, path->ants);
	if (color)
	{
		ft_memcpy(line, DISCOLOR, DISCOLOR_LN);
		line += DISCOLOR_LN;
	}
	*line = NL;
	write(fd, line - len + 1, len);
}

static inline void		print_flow(int fd, \
									char *line, \
									t_vector *colors, \
									t_flow *flow)
{
	static int			shift = FLOW_SHIFT_COLOR;
	t_path				**path;

	flow->paths->iter = -1;
	path = ft_vnext_con(flow->paths);
	if (colors)
	{
		print_header(fd, line, ft_vat(colors, CODE_PURPLE), flow->steps);
		while (path)
		{
			print_path(fd, line, ft_vat(colors, shift++ % MC), *path);
			path = ft_vnext_con(flow->paths);
		}
	}
	else
	{
		print_header(fd, line, NULL, flow->steps);
		while (path)
		{
			print_path(fd, line, NULL, *path);
			path = ft_vnext_con(flow->paths);
		}
	}
	ft_putchar_fd(NL, fd);
}

void					print_flows(t_display *d)
{
	char				line[MAX_FLOW_LN];
	t_flow				**flow;

	indent_control(d);
	d->flows->flows->iter = -1;
	flow = ft_vnext_con(d->flows->flows);
	if (d->colors)
		while (flow)
		{
			print_flow(d->fd, line, d->colors, *flow);
			flow = ft_vnext_con(d->flows->flows);
		}
	else
		while (flow)
		{
			print_flow(d->fd, line, NULL, *flow);
			flow = ft_vnext_con(d->flows->flows);
		}
}
