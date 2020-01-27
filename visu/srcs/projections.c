/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:36:43 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/23 10:46:05 by rnarbo           ###   ########.fr       */
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

void	my_proj_init(t_state *state)
{
	t_point angle;

	matrix_identity_set(state->obj.rot_m);
	angle = point_init(M_PI_4, -M_PI_4, 0);
	matrix_rotate(state->obj.rot_m, angle);
}

void	par_proj_init(t_state *state)
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

	k = -FOCUS_SHIFT_K * state->obj.radius * state->cam.scale /
		(point.z - FOCUS_SHIFT_K * state->obj.radius * state->cam.scale);
	point = point_init(point.x * k, point.y * k, point.z * k);
	return (point);
}
