/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:36:43 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/11 19:52:34 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "projections.h"
// #include "point.h"
// #include "draw_line.h"
#include "libft.h"
#include "matrix.h"

#include <stdlib.h>
#include <math.h>

void	iso_proj_init(t_state *state)
{
	matrix_identity_set(state->obj.rot_m);
	state->obj.rot_m[0][0] = sqrt(3.) / sqrt(6);
	state->obj.rot_m[0][2] = -sqrt(3.) / sqrt(6);
	state->obj.rot_m[1][0] = 1. / sqrt(6);
	state->obj.rot_m[1][1] = 2. / sqrt(6);
	state->obj.rot_m[1][2] = 1. / sqrt(6);
	state->obj.rot_m[2][0] = sqrt(2.) / sqrt(6);
	state->obj.rot_m[2][1] = -sqrt(2.) / sqrt(6);
	state->obj.rot_m[2][2] = sqrt(2.) / sqrt(6);
}

void	z_x_proj_init(t_state *state)
{
	t_point angle;

	matrix_identity_set(state->obj.rot_m);
	angle = point_init(M_PI_2, 0, 0);
	matrix_rotate(state->obj.rot_m, angle);
}

void	y_x_proj_init(t_state *state)
{
	matrix_identity_set(state->obj.rot_m);
}

t_point	ip_proj(t_point point, t_state *state)
{
	(void)state;
	return (point);
}

t_point	persp_proj(t_point point, t_state *state)
{
	double k;

	if (point.z >= FOCUS_SHIFT_K * state->obj.radius * state->cam.scale)
	{
		if (fabs(point.x) > fabs(point.y))
			k = state->graph.img.x_len / fabs(point.x);
		else
			k = state->graph.img.y_len / fabs(point.y);
	}
	else
		k = -FOCUS_SHIFT_K * state->obj.radius * state->cam.scale /
			(point.z - FOCUS_SHIFT_K * state->obj.radius * state->cam.scale);
	if (point.x == 0 && point.y == 0)
		point = point_init(0, 0, point.z);
	point = point_init(point.x * k, point.y * k, point.z);
	return (point);
}
