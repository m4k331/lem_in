/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:36:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/11 11:44:40 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "utils.h"

#include <math.h>

static void	bresenham_y(t_graphics *graph_p, t_point start,
	t_point end, unsigned int line_color)
{
	double	grad;
	t_point	p;
	int		i;
	double	gradz;

	i = start.y > end.y ? -1 : 1;
	p.x = start.x;
	p.y = ft_round(start.y);
	p.z = start.z;
	grad = (end.x - start.x) / (end.y - start.y) * i;
	gradz = (end.z - start.z) / (end.y - start.y) * i;
	while ((int)p.y * i < ft_round(end.y) * i)
	{
		if (p.y > 0 && p.y < graph_p->img.y_len - 1 &&
			ft_round(p.x) < graph_p->img.x_len - 1 && ft_round(p.x) > 0)
			if (graph_p->img.depth[(int)(p.y)][ft_round(p.x)] < p.z)
			{
				putpoint(graph_p, ft_round(p.x), (int)(p.y), line_color);
				graph_p->img.depth[(int)(p.y)][ft_round(p.x)] = p.z;
			}
		p.x += grad;
		p.y = (int)p.y + i;
		p.z += gradz;
	}
}

static void	bresenham_x(t_graphics *graph_p, t_point start,
	t_point end, unsigned int line_color)
{
	double	grad;
	t_point	p;
	int		i;
	double	gradz;

	i = start.x > end.x ? -1 : 1;
	p.x = ft_round(start.x);
	p.y = start.y;
	p.z = start.z;
	grad = (end.y - start.y) / (end.x - start.x) * i;
	gradz = (end.z - start.z) / (end.x - start.x) * i;
	while ((int)p.x * i <= ft_round(end.x) * i)
	{
		if (p.x > 0 && p.x < graph_p->img.x_len - 1 &&
			ft_round(p.y) < graph_p->img.y_len - 1 && ft_round(p.y) > 0)
			if (graph_p->img.depth[ft_round(p.y)][(int)p.x] < p.z)
			{
				putpoint(graph_p, (int)(p.x), ft_round(p.y), line_color);
				graph_p->img.depth[ft_round(p.y)][(int)(p.x)] = p.z;
			}
		p.y += grad;
		p.x = (int)p.x + i;
		p.z += gradz;
	}
}

void		bresenham(t_graphics *graph_p,
	t_point start, t_point end, unsigned int line_color)
{
	if ((start.x < 0 && end.x < 0) || (start.x > graph_p->img.x_len && end.x > graph_p->img.x_len) ||
		(start.y < 0 && end.y < 0) || (start.y > graph_p->img.y_len && end.y > graph_p->img.y_len))
		return ;
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
		bresenham_x(graph_p, start, end, line_color);
	else
		bresenham_y(graph_p, start, end, line_color);
}
