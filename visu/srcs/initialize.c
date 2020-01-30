/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:30:10 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/30 19:30:23 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "initialize.h"

//#include "point.h"
#include "projections.h"
//#include "render.h"
//#include "utils.h"
//#include "parse_file.h"
//#include "matrix.h"
#include "visu.h"
#include "draw.h"

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
}

double sqr(double x)
{
	return (x * x);
}

void	depth_free(double **matrix, size_t b)
{
	size_t i;

	i = 0;
	while (i < b)
		free(matrix[i++]);
	free(matrix);
}

double	**depth_alloc(size_t a, size_t b)
{
	double	**matrix;
	size_t	i;

	if ((matrix = (double **)malloc(a * sizeof(double *))) == 0)
		return (0);
	i = 0;
	while (i < a)
	{
		if ((matrix[i] = (double *)malloc(b * sizeof(double))) == 0)
		{
			depth_free(matrix, i);
			return (0);
		}
		i++;
	}
	return (matrix);
}

static void	img_init(t_graphics *graph_p, int x_size, int y_size)
{
	if ((graph_p->img.p = mlx_new_image(graph_p->mlx_p, x_size, y_size)) == 0)
		exit(-1);
	graph_p->img.data = mlx_get_data_addr(graph_p->img.p, &(graph_p->img.bpp),
			&(graph_p->img.line_size), &(graph_p->img.endian));
	if ((graph_p->img.duplicate =
		(char *)malloc(x_size * y_size * (graph_p->img.bpp / 8))) == 0) // TODO: check len
		exit(-1);
	graph_p->img.k = graph_p->img.line_size / (graph_p->img.bpp / 8);
	graph_p->img.x_len = x_size;
	graph_p->img.y_len = y_size;
	graph_p->img.depth = depth_alloc(graph_p->img.y_len, graph_p->img.x_len);
}

void rooms_centrize(t_obj *obj, t_point anchor)
{
	int i;

	i = 0;
	while (i < obj->rooms_cnt)
	{
		obj->rooms[i].pos.x -= anchor.x;
		obj->rooms[i].pos.y -= anchor.y;
		obj->rooms[i].pos.z -= anchor.z;
		i++;
	}
}

static void	obj_init(t_state *state, int map2circle)
{
	t_point		anchor;
	t_point		p_min;
	t_point		p_max;
	int			i;

	parse_input(&state->obj); // TODO:
	if (map2circle)
	{
		i = 0;
		while (i < state->obj.rooms_cnt)
		{
			state->obj.rooms[i].pos.x = sin(2 * M_PI * i / (state->obj.rooms_cnt));
			state->obj.rooms[i].pos.y = -cos(2 * M_PI * i / (state->obj.rooms_cnt));
			i++;
		}
	}
	p_max.x = -INFINITY;
	p_max.y = -INFINITY;
	p_max.z = -INFINITY;
	p_min.x = INFINITY;
	p_min.y = INFINITY;
	p_min.z = INFINITY;
	i = 0;
	while (i < state->obj.rooms_cnt)
	{
		if (state->obj.rooms[i].pos.x > p_max.x)
			p_max.x = state->obj.rooms[i].pos.x;
		if (state->obj.rooms[i].pos.y > p_max.y)
			p_max.y = state->obj.rooms[i].pos.y;
		if (state->obj.rooms[i].pos.z > p_max.z)
			p_max.z = state->obj.rooms[i].pos.z;
		if (state->obj.rooms[i].pos.x < p_min.x)
			p_min.x = state->obj.rooms[i].pos.x;
		if (state->obj.rooms[i].pos.y < p_min.y)
			p_min.y = state->obj.rooms[i].pos.y;
		if (state->obj.rooms[i].pos.z < p_min.z)
			p_min.z = state->obj.rooms[i].pos.z;
		i++;
	}
	anchor = point_init((p_max.x + p_min.x) / 2,
		(p_max.y + p_min.y) / 2,
		(p_max.z + p_min.z) / 2);
	rooms_centrize(&state->obj, anchor); // TODO: ?
	matrix_identity_set(state->obj.rot_m);
	// set_min_max(&x_min, &x_max, state);
	// set_min_max(&y_min, &y_max, state);
	// set_min_max(&z_min, &z_max, state);
	state->obj.radius = 
		sqrt(sqr((p_max.x - p_min.x) / 2) +
			sqr((p_max.y - p_min.y) / 2) +
			sqr((p_max.z - p_min.z) / 2));
}

void		print_rooms1(t_obj *obj)
{
	// TODO: delete

	t_room	*room = obj->rooms;
	int i = 0;

	while (i < obj->rooms_cnt)
	{
		printf("room #%d\n", i);
		printf("\tname: \'%s\'\n", room[i].name);
		printf("\tpos (%.1f, %.1f, %.1f)\n", room[i].pos.x, room[i].pos.y, room[i].pos.z);
		printf("\ttype: %s\n", (room[i].type == 0) ? "regular" : (room[i].type == 1) ? "start" : (room[i].type == 2) ? "end" : "I'm fucked up.");
		printf("\tcolor %#x\n\n", room[i].color);
		i++;
	}
}

void		state_init(t_state *state, int size_x, int size_y, int map2circle)
{
	obj_init(state, map2circle);

	if (size_x <= 0 || size_y <= 0)
		exit(-2);
	if ((state->graph.mlx_p = mlx_init()) == 0)
		exit(-3);
	if ((state->graph.w_p = mlx_new_window(state->graph.mlx_p,
					size_x, size_y, "lem_in visu")) == 0)
		exit(-4);
	img_init(&state->graph, size_x, size_y);
	camera_init(state);

	state->step = 0;
	state->step_percent = 0;
	state->image_changed = 1;
	state->pause = 0;
	state->auto_rotate = 0;
	state->speed = 0;
	state->menu = -1;

	print_rooms1(&state->obj);
	printf("radius: %f\n", state->obj.radius);
	printf("scale: %f\n", state->cam.scale);
	// exit(0);
	state->pr_init = (t_proj_init *)&par_proj_init;
	state->proj = (t_proj *)&ip_proj;
	state->draw_line = (t_draw_line *)&bresenham;
}
