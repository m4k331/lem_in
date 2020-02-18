/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiolin_wu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:36:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 02:26:24 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "visu.h"
#include "utils.h"
#include "draw.h"
#include "put.h"

#include <mlx.h>

static void	xiolin_putpoint_y(t_graphics *fdf_p, t_point p, unsigned int color)
{
	if (fdf_p->img.depth[(int)p.y][(int)p.x + stair(p.x)] < p.z)
	{
		putpoint(fdf_p, (int)p.x + stair(p.x), (int)p.y,
			intense(color, (1 - fpart(p.x)) > 0.5 ?
				1 - fpart(p.x) : fpart(p.x)));
		fdf_p->img.depth[(int)p.y][(int)p.x + stair(p.x)] = p.z;
		if (fdf_p->img.depth[(int)p.y][(int)p.x + 1 - stair(p.x)] < p.z)
			putpoint(fdf_p, (int)p.x + 1 - stair(p.x), (int)p.y,
				physical_intense_l1(
					mlx_get_color_value(fdf_p->mlx_p,
						intense(color, (1 - fpart(p.x)) > 0.5 ?
							fpart(p.x) : 1 - fpart(p.x))),
							((unsigned int *)fdf_p->img.data)[(int)p.x +
							1 - stair(p.x) + (int)p.y * fdf_p->img.k]));
	}
}

static void	xiolin_putpoint_x(t_graphics *fdf_p, t_point p, unsigned int color)
{
	if (fdf_p->img.depth[(int)p.y + stair(p.y)][(int)p.x] < p.z)
	{
		putpoint(fdf_p, (int)p.x, (int)p.y + stair(p.y),
			intense(color, (1 - fpart(p.y) > 0.5) ?
				1 - fpart(p.y) : fpart(p.y)));
		fdf_p->img.depth[(int)p.y + stair(p.y)][(int)p.x] = p.z;
		if (fdf_p->img.depth[(int)p.y + 1 - stair(p.y)][(int)p.x] < p.z)
			putpoint(fdf_p, (int)p.x, p.y + 1 - stair(p.y),
				physical_intense_l1(
					mlx_get_color_value(fdf_p->mlx_p,
						intense(color, (1 - fpart(p.y) > 0.5) ?
							fpart(p.y) : 1 - fpart(p.y))),
							((unsigned int *)fdf_p->img.data)[(int)p.x +
							(int)(p.y + 1 - stair(p.y)) * fdf_p->img.k]));
	}
}

static void	xiolin_wu_y(t_graphics *graph_p, t_point start,
	t_point end, unsigned int line_color)
{
	double	grad;
	double	gradz;
	t_point p;
	double	i;

	i = start.y > end.y ? -1 : 1;
	grad = (end.x - start.x) / (end.y - start.y) * i;
	gradz = (end.z - start.z) / (end.y - start.y) * i;
	p.x = start.x + grad * (ft_round(start.y) - start.y);
	p.y = ft_round(start.y);
	p.z = start.z;
	while ((int)p.y * i <= ft_round(end.y) * i)
	{
		if (p.y > 0 && (int)p.y < graph_p->img.y_len - 1 &&
			(int)p.x < graph_p->img.x_len - 1 && (int)p.x > 0)
			xiolin_putpoint_y(graph_p, point_init(p.x, p.y, p.z), line_color);
		p.z += gradz;
		p.y = (int)p.y + i;
		p.x += grad;
	}
}

static void	xiolin_wu_x(t_graphics *graph_p, t_point start,
	t_point end, unsigned int line_color)
{
	double	grad;
	double	gradz;
	t_point	p;
	int		i;

	i = start.x > end.x ? -1 : 1;
	grad = (end.y - start.y) / (end.x - start.x) * i;
	gradz = (end.z - start.z) / (end.x - start.x) * i;
	p.x = ft_round(start.x);
	p.y = start.y + grad * (ft_round(start.x) - start.x);
	p.z = start.z;
	while ((int)p.x * i <= ft_round(end.x) * i)
	{
		if (p.x > 0 && (int)p.x < graph_p->img.x_len - 1 &&
			(int)p.y < graph_p->img.y_len - 1 && (int)p.y > 0)
			xiolin_putpoint_x(graph_p, point_init(p.x, p.y, p.z), line_color);
		p.x = (int)p.x + i;
		p.y += grad;
		p.z += gradz;
	}
}

void		xiolin_wu(t_graphics *graph_p, t_point start,
	t_point end, unsigned int line_color)
{
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
		xiolin_wu_x(graph_p, start, end, line_color);
	else
		xiolin_wu_y(graph_p, start, end, line_color);
}
