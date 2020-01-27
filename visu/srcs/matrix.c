/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 22:16:17 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/19 04:48:24 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"

#include <math.h>

void	matrix_zero_set(double matrix[3][3], size_t a, size_t b)
{
	size_t j;

	j = 0;
	while (j < a)
		ft_memset(matrix[j++], 0, b * sizeof(double));
}

void	matrix_identity_set(double matrix[3][3])
{
	size_t i;

	i = 0;
	matrix_zero_set(matrix, 3, 3);
	while (i < 3)
	{
		matrix[i][i] = 1;
		i++;
	}
}

void	matrix_rmul(double matrix[3][3], double rotate_m[3][3])
{
	double	res[3][3];
	int		i;
	int		j;
	int		r;

	matrix_zero_set(res, 3, 3);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			r = -1;
			while (++r < 3)
				res[i][j] += rotate_m[i][r] * matrix[r][j];
		}
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			matrix[j][i] = res[j][i];
	}
}

void	matrix_rotate(double matrix[3][3], t_point angle)
{
	double rotate_m[3][3];
	double phi;
	double tht;
	double psi;

	phi = angle.x;
	tht = angle.y;
	psi = angle.z;
	matrix_identity_set(rotate_m);
	rotate_m[0][0] = cos(tht) * cos(psi);
	rotate_m[0][1] = -cos(phi) * sin(psi) + sin(phi) * sin(tht) * cos(psi);
	rotate_m[0][2] = sin(phi) * sin(psi) + cos(phi) * sin(tht) * cos(psi);
	rotate_m[1][0] = cos(tht) * sin(psi);
	rotate_m[1][1] = cos(phi) * cos(psi) + sin(phi) * sin(tht) * sin(psi);
	rotate_m[1][2] = -sin(phi) * cos(psi) + cos(phi) * sin(tht) * sin(psi);
	rotate_m[2][0] = -sin(tht);
	rotate_m[2][1] = sin(phi) * cos(tht);
	rotate_m[2][2] = cos(phi) * cos(tht);
	matrix_rmul(matrix, rotate_m);
}
