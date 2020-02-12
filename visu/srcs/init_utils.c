/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:23:12 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 22:24:47 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "visu.h"
#include "point.h"

#include <stdlib.h>

t_point	get_anchor(t_point **points, int len_x, int len_y)
{
	double	min;
	double	max;
	int		i;
	int		j;

	j = 0;
	min = (**points).z;
	max = min;
	while (j < len_y)
	{
		i = 0;
		while (i < len_x)
		{
			if (min > points[j][i].z)
				min = points[j][i].z;
			if (max < points[j][i].z)
				max = points[j][i].z;
			i++;
		}
		j++;
	}
	return (point_init(((double)len_x - 1) / 2.,
		-((double)len_y - 1) / 2., (max + min) / 2.));
}

int		set_min_max(int *z_min, int *z_max, t_state *state)
{
	double	min;
	double	max;
	int		j;
	int		i;

	j = -1;
	min = state->obj.map.points[0][0].z;
	max = state->obj.map.points[0][0].z;
	while (++j < state->obj.map.y_len && (i = -1) == -1)
		while (++i < state->obj.map.x_len)
		{
			if (min > state->obj.map.points[j][i].z)
				min = state->obj.map.points[j][i].z;
			if (max < state->obj.map.points[j][i].z)
				max = state->obj.map.points[j][i].z;
		}
	*z_min = min;
	*z_max = max;
	return (1);
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
