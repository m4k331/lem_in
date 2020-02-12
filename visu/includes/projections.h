/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:57 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 22:26:52 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIONS_H
# define PROJECTIONS_H

# include "visu.h"
# include <string.h>

# define FOCUS_SHIFT_K 2

void	iso_proj_init(t_state *state);
void	z_x_proj_init(t_state *state);
void	y_x_proj_init(t_state *state);

t_point	parallel_proj(t_point point, t_state *state);
t_point	perspective_proj(t_point point, t_state *state);

#endif
