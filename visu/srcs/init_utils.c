/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:23:12 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/14 18:55:50 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "visu.h"
// #include "point.h"

#include <stdlib.h>

double sqr(double x)
{
	return (x * x);
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
