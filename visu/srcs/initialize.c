/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:30:10 by rnarbo            #+#    #+#             */
/*   Updated: 2019/09/20 22:11:51 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

#include "point.h"
#include "projections.h"
#include "render.h"
#include "utils.h"
#include "parse_file.h"
#include "matrix.h"

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

static void	img_init(t_graphics *graph_p, int x_size, int y_size)
{
	if ((graph_p->img.p = mlx_new_image(graph_p->mlx_p, x_size, y_size)) == 0)
		exit(PERROR("Failed to allocate image"));
	graph_p->img.data = mlx_get_data_addr(graph_p->img.p, &(graph_p->img.bpp),
			&(graph_p->img.line_size), &(graph_p->img.endian));
	if ((graph_p->img.duplicate =
		(char *)malloc(x_size * y_size * (graph_p->img.bpp / 8))) == 0) // TODO: check len
		exit(PERROR("Failed to allocate image's duplicate!"));
	graph_p->img.k = graph_p->img.line_size / (graph_p->img.bpp / 8);
	graph_p->img.x_len = x_size;
	graph_p->img.y_len = y_size;
	graph_p->img.depth = depth_alloc(graph_p->img.y_len, graph_p->img.x_len);
}

static void	obj_init(t_state *state)
{
	t_point	anchor;
	int		z_min;
	int		z_max;

	parse_input(&state->obj); // TODO:

	anchor = get_anchor(state->obj.map.points,
			state->obj.map.x_len, state->obj.map.y_len);
	map_centrize(&state->obj.map, anchor); // TODO: ?
	matrix_identity_set(state->obj.rot_m);
	// set_min_max(&x_min, &x_max, state);
	// set_min_max(&y_min, &y_max, state);
	set_min_max(&z_min, &z_max, state);
	state->obj.radius =
		sqrt(sqr(anchor.x) + sqr(anchor.y) + sqr(z_max - z_min / 2)); // FIXME: x, y must be like z
}

void		state_init(t_state *state, int size_x, int size_y)
{
	obj_init(state);
	if (size_x <= 0 || size_y <= 0)
		exit(PERROR("Invalid window size!"));
	if ((state->graph.mlx_p = mlx_init()) == 0)
		exit(PERROR("Mlx initialization failed!"));
	if ((state->graph.w_p = mlx_new_window(state->graph.mlx_p,
					size_x, size_y, "lem_in visu")) == 0)
		exit(PERROR("Failed to create window!"));
	img_init(&state->graph, size_x, size_y);
	camera_init(state);

	state->step = 0;
	state->step_percent = 0;
	state->image_changed = 1;

	state->pr_init = (t_proj_init *)&par_proj_init;
	state->proj = (t_proj *)&ip_proj;
	state->draw_path = (t_draw_path *)&bresenham;
}
