/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:30:10 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 19:16:03 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projections.h"
#include "visu.h"
#include "draw.h"
#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include <mlx.h>

static void	camera_init(t_state *state)
{
	double scale;

	if (state->graph.img.x_len < state->graph.img.y_len)
		scale = (double)0.82 * state->graph.img.x_len / (2 * state->obj.radius);
	else
		scale = (double)0.82 * state->graph.img.y_len / (2 * state->obj.radius);
	state->cam.scale = scale;
	state->cam.zoom = point_init(1, 1, 1);
	state->cam.obs = point_init(
		state->graph.img.x_len / 2,
		state->graph.img.y_len / 2, 0);
	state->cam.shift = point_init(0, 0, 0);
	state->cam.speed = 0;
}

static void	img_init(t_graphics *graph_p, int x_size, int y_size)
{
	if ((graph_p->img.p = mlx_new_image(graph_p->mlx_p, x_size, y_size)) == 0)
		exit(-1);
	graph_p->img.data = mlx_get_data_addr(graph_p->img.p, &(graph_p->img.bpp),
			&(graph_p->img.line_size), &(graph_p->img.endian));
	if ((graph_p->img.duplicate =
		(char *)malloc(x_size * y_size * (graph_p->img.bpp / 8))) == 0)
		exit(-1);
	graph_p->img.k = graph_p->img.line_size / (graph_p->img.bpp / 8);
	graph_p->img.x_len = x_size;
	graph_p->img.y_len = y_size;
	graph_p->img.depth = depth_alloc(graph_p->img.y_len, graph_p->img.x_len);
}

static void	obj_init(t_state *state, int map2circle)
{
	t_point		anchor;
	t_point		p_min;
	t_point		p_max;
	int			i;

	parse_input(&state->obj);
	i = -1;
	while (map2circle && ++i < state->obj.rooms_cnt)
	{
		state->obj.rooms[i].pos.x = sin(2 * M_PI * i / (state->obj.rooms_cnt));
		state->obj.rooms[i].pos.y = -cos(2 * M_PI * i / (state->obj.rooms_cnt));
	}
	set_rooms_min_max(&p_min, &p_max, state);
	anchor = point_init((p_max.x + p_min.x) / 2,
		(p_max.y + p_min.y) / 2,
		(p_max.z + p_min.z) / 2);
	rooms_centrize(&state->obj, anchor);
	matrix_identity_set(state->obj.rot_m);
	state->obj.radius =
		sqrt(sqr((p_max.x - p_min.x) / 2) +
			sqr((p_max.y - p_min.y) / 2) +
			sqr((p_max.z - p_min.z) / 2));
}

static void	dynamics_init(t_state *state)
{
	state->dyn.step = 0;
	state->dyn.step_percent = 0;
	state->dyn.image_changed = 1;
	state->dyn.pause = 0;
	state->dyn.auto_rotate = 0;
	state->dyn.menu = -1;
	state->dyn.stat = -1;
	state->dyn.ant_speed = 1;
	state->dyn.time = 0;
	state->dyn.prev_mouse_pos = point_init(0, 0, 0);
}

void		state_init(t_state *state, int size_x, int size_y, int map2circle)
{
	obj_init(state, map2circle);
	size_x = size_x < MIN_WIN_SIZE_X ? MIN_WIN_SIZE_X : size_x;
	size_y = size_y < MIN_WIN_SIZE_Y ? MIN_WIN_SIZE_Y : size_y;
	if ((state->graph.mlx_p = mlx_init()) == 0)
		exit(-3);
	if ((state->graph.w_p = mlx_new_window(state->graph.mlx_p,
		size_x, size_y, "lem_in visu")) == 0)
		exit(-4);
	img_init(&state->graph, size_x, size_y);
	camera_init(state);
	dynamics_init(state);
	state->pr_init = (t_proj_init *)&y_x_proj_init;
	state->proj = (t_proj *)&parallel_proj;
	state->draw_line = (t_draw_line *)&bresenham;
}
