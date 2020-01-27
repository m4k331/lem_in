/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:30 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/19 04:22:10 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "point.h"
#include "visu.h"

int		point_is_zero(t_point p)
{
	if (p.x == 0 && p.y == 0 && p.z == 0)
		return (1);
	return (0);
}

t_point	point_init(double x, double y, double z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_point	point_minus(t_point a, t_point b)
{
	t_point res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_point	point_add(t_point a, t_point b)
{
	t_point res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_point	point_scale(t_point a, double k)
{
	t_point res;

	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}
