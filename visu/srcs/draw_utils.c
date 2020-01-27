/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:24:47 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/27 06:22:02 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "utils.h"
#include <math.h>

double			fpart(double a)
{
	return (a - (int)a);
}

int				stair(double num)
{
	return (ft_round(num) - (int)num);
}

unsigned int	intense(unsigned int color, double k)
{
	return ((unsigned int)((color & 0x0000ff) * k) +
	(((unsigned int)(((color & 0x00ff00) >> 8) * k)) << 8) +
	(((unsigned int)(((color & 0xff0000) >> 16) * k)) << 16));
}

// unsigned int	color_grad(t_point cur, t_line line,
// 	unsigned int color_s, unsigned int color_e)
// {
// 	double			k;
// 	unsigned int	res;
// 	unsigned char	bias;

// 	k = sqrt(sqr(cur.x - line.start.x) + sqr(cur.y - line.start.y)) /
// 		sqrt(sqr(line.end.x - line.start.x) + sqr(line.end.y - line.start.y));
// 	res = 0;
// 	bias = 0;
// 	if (k > 1)
// 		k = 1;
// 	while (bias <= 24)
// 	{
// 		res += (((unsigned int)(((color_s >> bias) & 0xff) *
// 						(1 - k)) + (unsigned int)(((color_e >> bias) & 0xff) *
// 							k)) & 0xff) << bias;
// 		bias += 8;
// 	}
// 	return (res);
// }

unsigned int	physical_intense_l1(unsigned int i1, unsigned int i2)
{
	unsigned int	a;
	unsigned int	res;
	unsigned char	bias;

	bias = 0;
	res = 0;
	while (bias <= 8 * 3)
	{
		a = (i1 >> bias & 0xff) + (i2 >> bias & 0xff);
		res += (a > 0xff ? 0xff : a) << bias;
		bias += 8;
	}
	return (res);
}
