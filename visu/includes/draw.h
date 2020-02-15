/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:58:12 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 15:30:04 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "visu.h"

void	putpoint(t_graphics *graph_p,
	int x, int y, unsigned int color);
void	bresenham(t_graphics *graph_p,
	t_point start, t_point end, unsigned int line_color);
void	xiolin_wu(t_graphics *graph_p,
	t_point start, t_point end, unsigned int line_color);
void	draw_no_line(t_graphics *graph_p,
	t_point start, t_point end, unsigned int line_color);

#endif
