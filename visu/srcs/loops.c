/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:27:18 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/14 19:20:14 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loops.h"
#include "visu.h"
#include "mlx.h"

#include <math.h>

int		slow_rotate(t_state *state)
{
	t_point	val;

	if (state->dyn.auto_rotate)
	{
		val = point_init(0, M_PI * (state->cam.speed + 1) / 360, 0);
		matrix_rotate(state->obj.rot_m, val);
		state->dyn.image_changed = 1;
		render(state);
	}
	if (!state->dyn.pause)
		mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	return (0);
}

int		ants_loop(t_state *state)
{
	static char i = 0;

	if (!state->dyn.pause)
	{
		state->dyn.step_percent = 50 +
			50 * sin(M_PI / 100 * state->dyn.time * state->dyn.ant_speed - M_PI_2);
		state->dyn.time++;
		if (state->dyn.ant_speed * state->dyn.time > 100)
		{
			state->dyn.step_percent = 0;
			state->dyn.time = 0;
			state->dyn.step++;
		}
		render(state);
	}
	i = (i + 1) % 4;
	if (state->dyn.auto_rotate && i == 0)
		mlx_loop_hook(state->graph.mlx_p, &slow_rotate, state);
	return (0);
}
