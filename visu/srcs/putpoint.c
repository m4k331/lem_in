/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpoint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:47:29 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/21 10:08:58 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "putpoint.h"
#include <mlx.h>

void	putpoint(t_graphics *graph_p, int x, int y, unsigned int color)
{
	// if (x < graph_p->img.x_len - 1 && x > 0 && y < graph_p->img.y_len - 1 && y > 0)
	((unsigned int *)graph_p->img.data)[x + y * graph_p->img.k] =
		mlx_get_color_value(graph_p->mlx_p, color);
}
