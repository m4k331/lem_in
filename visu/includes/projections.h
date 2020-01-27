/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:41:57 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/23 10:44:01 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIONS_H
# define PROJECTIONS_H

# include "visu.h"
# include <string.h>

# define FOCUS_SHIFT_K 3

void	iso_proj_init(t_state *state);
void	par_proj_init(t_state *state);
void	my_proj_init(t_state *state);

t_point	ip_proj(t_point point, t_state *state);
t_point	persp_proj(t_point point, t_state *state);

#endif
