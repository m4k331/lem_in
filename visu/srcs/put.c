/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:47:29 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 18:05:35 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "utils.h"
#include <mlx.h>

void	putpoint(t_graphics *graph_p, int x, int y, unsigned int color)
{
	((unsigned int *)graph_p->img.data)[x + y * graph_p->img.k] =
		mlx_get_color_value(graph_p->mlx_p, color);
}

void	put_ant(t_state *st, t_point ant_pos, int color)
{
	int i;
	int j;

	i = -ANT_SIZE - 1;
	while (++i <= ANT_SIZE)
	{
		j = -ANT_SIZE - 1;
		while (++j <= ANT_SIZE)
			if (ft_round(ant_pos.x) + i > 0 &&
				ft_round(ant_pos.x) + i < st->graph.img.x_len &&
				ft_round(ant_pos.y) + j > 0 &&
				ft_round(ant_pos.y) + j < st->graph.img.y_len)
				if (st->graph.img.depth
					[ft_round(ant_pos.y) + j][ft_round(ant_pos.x) + i] <
					ant_pos.z + 1)
					putpoint(&st->graph,
						ft_round(ant_pos.x) + i,
						ft_round(ant_pos.y) + j, color);
	}
}

void	put_room(t_state *st, t_room *r)
{
	int i;
	int j;

	i = -ROOM_SIZE - 1;
	while (++i <= ROOM_SIZE)
	{
		j = -ROOM_SIZE - 1;
		while (++j <= ROOM_SIZE)
			if (ft_round(r->pos.x) + i > 0 &&
				ft_round(r->pos.x) + i < st->graph.img.x_len &&
				ft_round(r->pos.y) + j > 0 &&
				ft_round(r->pos.y) + j < st->graph.img.y_len)
				if (st->graph.img.depth
					[ft_round(r->pos.y) + j][ft_round(r->pos.x) + i] <
					r->pos.z + 1)
				{
					putpoint(&st->graph,
						ft_round(r->pos.x) + i,
						ft_round(r->pos.y) + j, r->color);
					st->graph.img.depth
						[ft_round(r->pos.y) + j][ft_round(r->pos.x) + i] =
							r->pos.z + 1;
				}
	}
}
