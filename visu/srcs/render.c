/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:28:50 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 20:08:02 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "projections.h"
#include "render.h"

#include <float.h>
#include <mlx.h>

static t_point	get_ant_position(t_point start, t_point end, double percent)
{
	t_point result;

	result.x = start.x + (end.x - start.x) * percent / 100;
	result.y = start.y + (end.y - start.y) * percent / 100;
	result.z = start.z + (end.z - start.z) * percent / 100;
	return (result);
}

static void		draw_ants_movement(t_state *state)
{
	int		i;
	int		j;
	t_room	**route;
	t_point	ant_pos;
	char	flag;

	i = -1;
	flag = 1;
	while (++i < state->obj.ants_cnt &&
		state->obj.ants_traces[i].step <= state->dyn.step)
	{
		route = state->obj.routes[state->obj.ants_traces[i].route];
		j = state->dyn.step - state->obj.ants_traces[i].step;
		if (j + 1 < route_len(route))
		{
			flag = 0;
			ant_pos = transform(state,
				get_ant_position(
					route[j]->pos, route[j + 1]->pos,
					state->dyn.step_percent));
			put_ant(state, ant_pos, ANT_COLOR);
		}
	}
	if (flag)
		state->dyn.pause = 1;
}

static void		draw_connections(t_state *state)
{
	int		i;
	int		j;
	t_point	start;
	t_point	end;

	j = -1;
	while (++j < state->obj.cons_cnt)
	{
		start = transform(state, state->obj.cons[j].r1->pos);
		end = transform(state, state->obj.cons[j].r2->pos);
		clipping(&start, &end, state);
		if (state->proj != perspective_proj ||
			((start.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale ||
				end.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale)))
			if (!(start.x < 0 && end.x < 0) &&
				!(start.x > state->graph.img.x_len &&
				end.x > state->graph.img.x_len))
				state->draw_line(&state->graph,
					start, end, state->obj.cons[j].color);
	}
}

static void		recalculate_image(t_state *state)
{
	int		i;
	int		j;
	t_room	room;
	t_point start;
	t_point end;

	ft_memset(state->graph.img.data, 0,
		state->graph.img.y_len * state->graph.img.line_size);
	j = -1;
	while (++j < state->graph.img.y_len && (i = -1) == -1)
		while (++i < state->graph.img.x_len)
			state->graph.img.depth[j][i] = -DBL_MAX;
	draw_connections(state);
	j = -1;
	while (++j < state->obj.rooms_cnt)
	{
		room = state->obj.rooms[j];
		room.pos = transform(state, state->obj.rooms[j].pos);
		put_room(state, &room);
	}
	ft_memmove(state->graph.img.duplicate, state->graph.img.data,
		state->graph.img.y_len * state->graph.img.line_size);
}

void			render(t_state *state)
{
	if (state->dyn.image_changed)
		recalculate_image(state);
	else
		ft_memmove(state->graph.img.data, state->graph.img.duplicate,
			state->graph.img.y_len * state->graph.img.line_size);
	draw_ants_movement(state);
	if (state->dyn.menu)
		render_menu_board(state,
			point_init(state->graph.img.x_len - MIN_WIN_SIZE_X, 0, 0),
			point_init(state->graph.img.x_len, state->graph.img.y_len, 0));
	if (state->dyn.stat)
		render_menu_board(state, point_init(0, 0, 0),
			point_init(MIN_WIN_SIZE_X, state->graph.img.y_len, 0));
	mlx_clear_window(state->graph.mlx_p, state->graph.w_p);
	mlx_put_image_to_window(state->graph.mlx_p, state->graph.w_p,
		state->graph.img.p, 0, 0);
	if (state->dyn.stat)
		render_stat(state, point_init(0, 0, 0));
	if (state->dyn.menu)
		render_menu(state,
			point_init(state->graph.img.x_len - MIN_WIN_SIZE_X, 0, 0));
	state->dyn.image_changed = 0;
}
