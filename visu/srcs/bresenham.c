/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:36:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/27 06:27:44 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "visu.h"
// #include "utils.h"
// #include "draw_line.h"
// #include "point.h"
#include "putpoint.h"

int ft_round(double x)
{
	return ((int)(x + 0.5));
}

// static void	bresenham_y(t_fdf *graph_p, t_line line,
// 	unsigned int color_s, unsigned int color_e)
// {
// 	double	grad;
// 	double	xi;
// 	int		yi;
// 	double	zi;
// 	double	gradz;

// 	grad = (line.end.x - line.start.x) / (line.end.y - line.start.y);
// 	xi = line.start.x;
// 	yi = ft_round(line.start.y);
// 	zi = line.start.z;
// 	gradz = (line.end.z - line.start.z) / (line.end.y - line.start.y);
// 	while (yi < line.end.y && yi < graph_p->img.y_len - 1)
// 	{
// 		if (yi > 0 && ft_round(xi) < graph_p->img.x_len - 1 && ft_round(xi) > 0)
// 			if (graph_p->img.depth[(yi)][ft_round(xi)] < zi)
// 			{
// 				putpoint(graph_p, ft_round(xi), (yi), color_grad(
// 					point_init(ft_round(xi), (yi), 0), line, color_s, color_e));
// 				graph_p->img.depth[(yi)][ft_round(xi)] = zi;
// 			}
// 		xi += grad;
// 		yi++;
// 		zi += gradz;
// 	}
// }

// static void	bresenham_x(t_fdf *graph_p, t_line line,
// 	unsigned int color_s, unsigned int color_e)
// {
// 	double	grad;
// 	int		xi;
// 	double	yi;
// 	double	zi;
// 	double	gradz;

// 	grad = (line.end.y - line.start.y) / (line.end.x - line.start.x);
// 	xi = ft_round(line.start.x);
// 	yi = line.start.y;
// 	zi = line.start.z;
// 	gradz = (line.end.z - line.start.z) / (line.end.x - line.start.x);
// 	while (xi < line.end.x && xi < graph_p->img.x_len - 1)
// 	{
// 		if (xi > 0 && ft_round(yi) < graph_p->img.y_len - 1 && ft_round(yi) > 0)
// 			if (graph_p->img.depth[ft_round(yi)][xi] < zi)
// 			{
// 				putpoint(graph_p, (xi), ft_round(yi), color_grad(
// 					point_init((xi), ft_round(yi), 0), line, color_s, color_e));
// 				graph_p->img.depth[ft_round(yi)][(xi)] = zi;
// 			}
// 		yi += grad;
// 		xi++;
// 		zi += gradz;
// 	}
// }

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
	printf("grad: %f\n", grad);
	while ((int)p.y * i < ft_round(end.y) * i)
	{
		// printf("start: %f now: %f end: %f i: %d\n", start->pos.y, p.y, end->pos.y, i);
		if (p.y > 0 && p.y < graph_p->img.y_len - 1 && ft_round(p.x) < graph_p->img.x_len - 1 && ft_round(p.x) > 0)
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
	printf("grad: %f\n", grad);
	printf("(%f, %f)\n", start.y, end.y);
	while ((int)p.x * i <= ft_round(end.x) * i)
	{
		printf("(%f, %f, %f)\n", p.x, p.y, p.z);
		// printf("start: %f now: %f end: %f\n", start->pos.x, p.x, end->pos.x);
		if (p.x > 0 && p.x < graph_p->img.x_len - 1 /* was in while cond */ &&
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

void		bresenham(t_graphics *graph_p, t_point start, t_point end, unsigned int line_color)
{
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
		bresenham_x(graph_p, start, end, line_color);
	else
		bresenham_y(graph_p, start, end, line_color);
	// if (fabs(r1->pos.z - graph_p->img.depth[(int)r1->pos.x][(int)r1->pos.y]) <= __DBL_EPSILON__ * 2)
	// 	putpoint(graph_p, r1->pos.x, r1->pos.y, r1->color);
	// if (fabs(r2->pos.z - graph_p->img.depth[(int)r2->pos.x][(int)r2->pos.y]) <= __DBL_EPSILON__ * 2)
	// 	putpoint(graph_p, r2->pos.x, r2->pos.y, r2->color);
}
