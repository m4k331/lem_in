/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:08:07 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/14 19:20:01 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "key_bindings.h"
#include "mlx.h"
#include "render.h"

#include <math.h>

int		mouse_shift_handle(int x, int y, t_state *state)
{
	state->cam.shift = point_init(
		state->cam.shift.x + (x - state->dyn.prev_mouse_pos.x),
		state->cam.shift.y + (y - state->dyn.prev_mouse_pos.y),
		state->cam.shift.z);
	state->dyn.prev_mouse_pos = point_init(x, y, 0);
	state->dyn.image_changed = 1;
	render(state);
	return (0);
}

int		mouse_shift_z_handle(int x, int y, t_state *state)
{
	(void)x;
	state->cam.shift = point_init(
		state->cam.shift.x,
		state->cam.shift.y,
		state->cam.shift.z + (y - state->dyn.prev_mouse_pos.z));
	state->dyn.prev_mouse_pos = point_init(0, 0, y);
	state->dyn.image_changed = 1;
	render(state);
	return (0);
}

int		mouse_wheel_handle(int button, int x, int y, t_state *st)
{
	double	sign;

	(void)x;
	(void)y;
	sign = (button == MOUSE_WHL_UP ? 1 : -0.5);
	if ((button == MOUSE_WHL_UP || button == MOUSE_WHL_DOWN) &&
		st->cam.scale + sign * (st->cam.speed ? st->cam.scale : 1 / fabs(sign)) > 0)
		st->cam.scale = st->cam.scale +
			sign * (st->cam.speed ? st->cam.scale : 1 / fabs(sign));
	st->dyn.image_changed = 1;
	render(st);
	return (0);
}

int		mouse_press(int button, int x, int y, t_state *state)
{
	if (button == 4 || button == 5)
		mouse_wheel_handle(button, x, y, state);
	if (button == MOUSE_BR)
	{
		state->dyn.prev_mouse_pos = point_init(x, y, 0);
		mlx_hook(state->graph.w_p, 6, 0, &mouse_shift_handle, state);
	}
	if (button == MOUSE_BL)
	{
		state->dyn.prev_mouse_pos = point_init(0, 0, y);
		mlx_hook(state->graph.w_p, 6, 0, &mouse_shift_z_handle, state);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	if (button != MOUSE_BR && button != MOUSE_BL)
		return (0);
	mlx_hook(state->graph.w_p, 6, 0, 0, 0);
	return (0);
}
