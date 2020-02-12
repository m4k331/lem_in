/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:27:18 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 22:25:28 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loops.h"
#include "visu.h"
#include "mlx.h"

#include <math.h>

int		slow_rotate(t_state *state)
{
	t_point	val;

	if (state->auto_rotate)
	{
		val = point_init(0, M_PI * (state->speed + 1) / 360, 0);
		matrix_rotate(state->obj.rot_m, val);
		state->image_changed = 1;
		render(state);
	}
	if (!state->pause)
		mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	return (0);
}

int		ants_loop(t_state *state)
{
	static char i = 0;

	if (!state->pause)
	{
		state->step_percent = 50 +
			50 * sin(M_PI / 100 * state->time * state->ant_speed - M_PI_2);
		state->time++;
		if (state->ant_speed * state->time > 100)
		{
			state->step_percent = 0;
			state->time = 0;
			state->step++;
		}
		render(state);
	}
	i = (i + 1) % 4;
	if (state->auto_rotate && i == 0)
		mlx_loop_hook(state->graph.mlx_p, &slow_rotate, state);
	return (0);
}
