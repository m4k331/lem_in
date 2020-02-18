/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:24:47 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/11 11:40:34 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "utils.h"
#include <math.h>

int				ft_round(double x)
{
	return ((int)(x + 0.5));
}

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
