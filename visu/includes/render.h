/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:13:14 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 15:31:29 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "visu.h"

void			clipping(t_point *start, t_point *end, t_state *state);
t_point			transform(t_state *state, t_point point);
unsigned int	menu_intense_reducing(
					unsigned int i1,
					unsigned int i2,
					double transparency_k);
void			render_menu_board(t_state *state, t_point start, t_point end);
void			render_stat(t_state *state, t_point start);
void			render_menu(t_state *state, t_point start);
void			render(t_state *state);

#endif
