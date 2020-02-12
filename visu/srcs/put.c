/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:47:29 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 19:43:41 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <mlx.h>

void	putpoint(t_graphics *graph_p, int x, int y, unsigned int color)
{
	// if (x < graph_p->img.x_len - 1 && x > 0 && y < graph_p->img.y_len - 1 && y > 0)
	((unsigned int *)graph_p->img.data)[x + y * graph_p->img.k] =
		mlx_get_color_value(graph_p->mlx_p, color);
}

void put_ant(t_state *state, t_point ant_pos, int color)
{
	int i = -2;
	int j;

	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (ft_round(ant_pos.x) + i > 0 && ft_round(ant_pos.x) + i < state->graph.img.x_len &&
				ft_round(ant_pos.y) + j > 0 && ft_round(ant_pos.y) + j < state->graph.img.y_len)
				if (state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(ant_pos.x) + i] <
					ant_pos.z + 1)
				{
					putpoint(&state->graph, ft_round(ant_pos.x) + i, ft_round(ant_pos.y) + j, color);
					// state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(ant_pos.x) + i] = ant_pos.z + 1;
				}
			// else
			// {
				// printf("color: %x (%d, %d, %f) depth: %f\n", color, i, j, ant_pos.z, state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(room->pos.x) + i]);
			// }
			j++;
		}
		i++;
	}
}

void put_room(t_state *state, t_room *room)
{
	int i = -3;
	int j;

	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			if (ft_round(room->pos.x) + i > 0 && ft_round(room->pos.x) + i < state->graph.img.x_len &&
				ft_round(room->pos.y) + j > 0 && ft_round(room->pos.y) + j< state->graph.img.y_len)
			{
				if (state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i] <
					room->pos.z + 1)
				{
					putpoint(&state->graph, ft_round(room->pos.x) + i, ft_round(room->pos.y) + j, room->color);
					state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i] = room->pos.z + 1;
				}
				else
				{
					printf("color: %x (%d, %d, %f) depth: %f\n", room->color, i, j, room->pos.z, state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i]);
				}
			}
			j++;
		}
		i++;
	}
}
