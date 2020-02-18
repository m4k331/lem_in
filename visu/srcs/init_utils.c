/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:23:12 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 13:40:32 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "visu.h"

#include <stdlib.h>
#include <math.h>

double	sqr(double x)
{
	return (x * x);
}

void	rooms_centrize(t_obj *obj, t_point anchor)
{
	ssize_t i;

	i = 0;
	while (i < obj->rooms_cnt)
	{
		obj->rooms[i].pos.x -= anchor.x;
		obj->rooms[i].pos.y -= anchor.y;
		obj->rooms[i].pos.z -= anchor.z;
		i++;
	}
}

void	set_rooms_min_max(t_point *min, t_point *max, t_state *state)
{
	ssize_t i;

	*max = point_init(-INFINITY, -INFINITY, -INFINITY);
	*min = point_init(INFINITY, INFINITY, INFINITY);
	i = -1;
	while (++i < state->obj.rooms_cnt)
	{
		if (state->obj.rooms[i].pos.x > max->x)
			max->x = state->obj.rooms[i].pos.x;
		if (state->obj.rooms[i].pos.y > max->y)
			max->y = state->obj.rooms[i].pos.y;
		if (state->obj.rooms[i].pos.z > max->z)
			max->z = state->obj.rooms[i].pos.z;
		if (state->obj.rooms[i].pos.x < min->x)
			min->x = state->obj.rooms[i].pos.x;
		if (state->obj.rooms[i].pos.y < min->y)
			min->y = state->obj.rooms[i].pos.y;
		if (state->obj.rooms[i].pos.z < min->z)
			min->z = state->obj.rooms[i].pos.z;
	}
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
