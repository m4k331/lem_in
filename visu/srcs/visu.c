/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:49:44 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 02:33:07 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "key_bindings.h"
#include "event_handling.h"
#include "projections.h"
#include "draw.h"
#include "loops.h"
#include "render.h"

#include <mlx.h>

static void	dynamics_handle(int keycode, t_state *state)
{
	if (keycode == KEY_H)
		state->dyn.menu = !state->dyn.menu;
	if (keycode == KEY_G)
	{
		state->dyn.step = 0;
		state->dyn.step_percent = 0;
		state->dyn.pause = 0;
		state->dyn.time = 0;
	}
	if (keycode == KEY_F)
		state->dyn.pause = !state->dyn.pause;
	if (keycode == KEY_SPACE)
		state->dyn.auto_rotate = !state->dyn.auto_rotate;
	if (keycode == KEY_TILDA)
		state->dyn.stat = !state->dyn.stat;
	if (keycode == KEY_PAGE_UP)
		state->dyn.ant_speed = state->dyn.ant_speed > 10 ?
			10 : state->dyn.ant_speed + 0.1;
	if (keycode == KEY_PAGE_DOWN)
		state->dyn.ant_speed = state->dyn.ant_speed < 0.2 ?
			0.2 : state->dyn.ant_speed - 0.1;
	if (keycode == KEY_PAGE_DOWN || keycode == KEY_PAGE_UP)
		state->dyn.time = 0;
}

static int	key_hook(int keycode, t_state *state)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_Q)
		state->cam.speed = 0;
	if (keycode == KEY_E)
		state->cam.speed += 1;
	if (rotate_handle(keycode, state) ||
		zoom_handle(keycode, state) ||
		proj_handle(keycode, state) ||
		render_handle(keycode, state))
		state->dyn.image_changed = 1;
	dynamics_handle(keycode, state);
	render(state);
	return (0);
}

static int	close_on_red(void *par)
{
	(void)par;
	exit(0);
}

int			visu(t_state *state)
{
	state->pr_init(state);
	state->dyn.image_changed = 1;
	render(state);
	mlx_hook(state->graph.w_p, 2, 0, &key_hook, state);
	mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	mlx_hook(state->graph.w_p, 4, 0, &mouse_press, state);
	mlx_hook(state->graph.w_p, 5, 0, &mouse_release, state);
	mlx_hook(state->graph.w_p, 17, 0, &close_on_red, state);
	mlx_loop(state->graph.mlx_p);
	return (0);
}
