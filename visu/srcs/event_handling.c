/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:08:23 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/28 09:07:20 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "projections.h"
// #include "render.h"
// #include "point.h"
#include "event_handling.h"
#include "key_bindings.h"
#include "bresenham.h"
#include "xiolin_wu.h"
// #include "draw_line.h"
#include "matrix.h"

#include <math.h>
#include <stdlib.h>
#include <mlx.h>

int	rotate_handle(int keycode, t_state *state)
{
	t_point	angle;
	int		sign;

	sign = (keycode == KEY_ARR_U || keycode == KEY_ARR_R ? 1 : -1);
	if (keycode == KEY_ARR_U || keycode == KEY_ARR_D ||
		keycode == KEY_ARR_L || keycode == KEY_ARR_R)
	{
		if (keycode == KEY_ARR_U || keycode == KEY_ARR_D)
		{
			angle = point_init(M_PI * sign *
				(state->speed * 2 + 4) / 360, 0, 0);
			matrix_rotate(state->obj.rot_m, angle);
		}
		if (keycode == KEY_ARR_R || keycode == KEY_ARR_L)
		{
			angle = point_init(0, M_PI * sign *
				(state->speed * 2 + 4) / 360, 0);
			matrix_rotate(state->obj.rot_m, angle);
		}
		return (1);
	}
	return (0);
}

int	shift_handle(int keycode, t_state *state)
{
	int sign;

	if (keycode == KEY_0 || keycode == KEY_A || keycode == KEY_S ||
		keycode == KEY_D || keycode == KEY_W)
	{
		sign = (keycode == KEY_A || keycode == KEY_W ? 1 : -1);
		if (keycode == KEY_0)
			state->cam.shift = point_init(0, 0, 0);
		if (keycode == KEY_A || keycode == KEY_D)
			state->cam.shift = point_init(
				state->cam.shift.x + sign * (1 + state->speed),
				state->cam.shift.y, state->cam.shift.z);
		if (keycode == KEY_W || keycode == KEY_S)
			state->cam.shift = point_init(
				state->cam.shift.x,
				state->cam.shift.y + sign * (1 + state->speed),
				state->cam.shift.z);
		return (1);
	}
	return (0);
}

int	zoom_handle(int keycode, t_state *st)
{
	double sign;

	if (keycode != KEY_PLUS && keycode != KEY_MINUS &&
		keycode != KEY_LESS && keycode != KEY_GRTR && keycode != KEY_CR_BRACKET && keycode != KEY_CL_BRACKET)
		return (0);
	sign = (keycode == KEY_PLUS || keycode == KEY_GRTR || keycode == KEY_CR_BRACKET ? 1 : -0.5);
	if ((keycode == KEY_PLUS || keycode == KEY_MINUS) && st->cam.scale +
			sign * (st->speed ? st->cam.scale : 1 / fabs(sign)) > 0)
		st->cam.scale = st->cam.scale +
			sign * (st->speed ? st->cam.scale : 1 / fabs(sign));
	if ((keycode == KEY_LESS && st->cam.zoom.z + sign *
		(st->speed ? st->cam.zoom.z : 0.1 / fabs(sign)) >= -FOCUS_SHIFT_K) ||
		(keycode == KEY_GRTR && st->cam.zoom.z + sign *
		(st->speed ? st->cam.zoom.z : 0.1 / fabs(sign)) <= FOCUS_SHIFT_K))
		st->cam.zoom = point_init(
			(st->cam.zoom.x), (st->cam.zoom.y),
			(st->cam.zoom.z + sign *
				(st->speed ? st->cam.zoom.z : 0.1 / fabs(sign))));
	if (keycode == KEY_CR_BRACKET || keycode == KEY_CL_BRACKET)
		st->cam.zoom = point_init(
			st->cam.zoom.x + sign *
				(st->speed ? st->cam.zoom.x : 0.1 / fabs(sign)),
			st->cam.zoom.x + sign *
				(st->speed ? st->cam.zoom.y : 0.1 / fabs(sign)),
			st->cam.zoom.z
		);
	return (1);
}

int	proj_handle(int keycode, t_state *st)
{
	if (keycode == KEY_1 || keycode == KEY_2 ||
		keycode == KEY_3 || keycode == KEY_4)
	{
		st->proj = (t_proj *)&ip_proj;
		st->pr_init = (t_proj_init *)&par_proj_init;
		if (keycode == KEY_1)
			st->pr_init = (t_proj_init *)&my_proj_init;
		if (keycode == KEY_2)
			st->pr_init = (t_proj_init *)&iso_proj_init;
		if (keycode == KEY_4)
			st->proj = (t_proj *)&persp_proj;
		st->pr_init(st);
		return (1);
	}
	return (0);
}

int	render_handle(int keycode, t_state *st)
{
	if (keycode == KEY_R || keycode == KEY_X || keycode == KEY_B ||
		keycode == KEY_P || keycode == KEY_C)
	{
		if (keycode == KEY_R)
		{
			st->speed = 0;
			st->cam.shift = point_init(0, 0, 0);
			st->cam.scale = 0.82 *
				(double)(st->graph.img.x_len < st->graph.img.y_len ?
				st->graph.img.x_len : st->graph.img.y_len) / (2 * st->obj.radius);
			st->cam.zoom = point_init(1, 1, 1);
			st->pr_init(st);
		}
		if (keycode == KEY_X)
			st->draw_line = &xiolin_wu;
		if (keycode == KEY_B)
			st->draw_line = &bresenham;
		// if (keycode == KEY_P)
		// 	st->draw_cell = (t_draw_cell *)&point_cell;
		// if (keycode == KEY_C)
		// 	st->color = st->color ? 0 : 1;
		return (1);
	}
	return (0);
}
