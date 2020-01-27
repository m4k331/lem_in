/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:51 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/27 06:20:09 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// # include "point.h"
# include <stdlib.h>

/*
** Render utils
*/
// int				is_line_in_window(t_state *state, t_point start, t_point end);
// t_point			transform(t_state *state, t_point point);

/*
** Initialize utils
*/
// void			depth_free(double **matrix, size_t b);
// double			**depth_alloc(size_t a, size_t b);
// // void			map_centrize(t_map *map, t_point anchor);
// t_point			get_anchor(t_point **points, int len_x, int len_y);
// int				set_min_max(int *z_min, int *z_max, t_state *state);

/*
** Math utils
*/
int				ft_round(double num);
void			swap(double *a, double *b);
void			swap_ul(unsigned int *a, unsigned int *b);
double			fpart(double a);
double			sqr(double a);

/*
** Draw utils
*/
unsigned int	intense(unsigned int color, double k);
unsigned int	physical_intense_l1(unsigned int i1, unsigned int i2);
int				stair(double num);
// unsigned int	color_grad(t_point cur, t_line line,
	// unsigned int color_s, unsigned int color_e);

#endif
