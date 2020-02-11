/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:57 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/10 08:25:35 by rnarbo           ###   ########.fr       */
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

t_point	ip_proj(t_point point, t_state *state);
t_point	persp_proj(t_point point, t_state *state);

#endif
