/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 22:17:00 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/19 04:47:58 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "visu.h"
# include <stdlib.h>

void	matrix_zero_set(double matrix[3][3], size_t a, size_t b);
void	matrix_identity_set(double matrix[3][3]);
void	matrix_rmul(double matrix_a[3][3], double matrix_b[3][3]);
void	matrix_rotate(double matrix[3][3], t_point angle);

#endif
