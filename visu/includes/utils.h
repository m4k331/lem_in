/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:51 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 15:56:53 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "visu.h"
# include <stdlib.h>

/*
** Render utils
*/

/*
** Initialize utils
*/

double			sqr(double x);
void			rooms_centrize(t_obj *obj, t_point anchor);
void			depth_free(double **matrix, size_t b);
double			**depth_alloc(size_t a, size_t b);
void			set_rooms_min_max(t_point *min, t_point *max, t_state *state);

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

#endif
