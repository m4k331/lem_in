/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:16:44 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 22:28:03 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	clip_x(t_point *p1, t_point *p2, t_state *st)
{
	t_point tmp;

	if (p1->x < 0)
	{
		tmp.x = 0;
		tmp.y = p1->y - (p1->y - p2->y) / (p1->x - p2->x) * p1->x;
	}
	if (p1->x > st->graph.img.x_len)
	{
		tmp.x = st->graph.img.x_len;
		tmp.y = p1->y -
			(p1->y - p2->y) / (p1->x - p2->x) * (p1->x - st->graph.img.x_len);
	}
	*p1 = tmp;
}

void	clip_y(t_point *p1, t_point *p2, t_state *st)
{
	t_point tmp;

	if (p1->y < 0)
	{
		tmp.y = 0;
		tmp.x = p1->x - (p1->x - p2->x) / (p1->y - p2->y) * p1->y;
	}
	if (p1->y > st->graph.img.y_len)
	{
		tmp.y = st->graph.img.y_len;
		tmp.x = p1->x -
			(p1->x - p2->x) / (p1->y - p2->y) * (p1->y - st->graph.img.y_len);
	}
	*p1 = tmp;
}

void	clipping(t_point *start, t_point *end, t_state *st)
{
	if (start->x < 0 || start->x > st->graph.img.x_len)
		clip_x(start, end, st);
	if (end->x < 0 || end->x > st->graph.img.x_len)
		clip_x(end, start, st);
	if (start->y < 0 || start->y > st->graph.img.y_len)
		clip_y(start, end, st);
	if (end->y < 0 || end->y > st->graph.img.y_len)
		clip_y(end, start, st);
}
