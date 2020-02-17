/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 02:24:24 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 02:24:24 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H

#include "visu.h"

void	putpoint(t_graphics *graph_p,
	int x, int y, unsigned int color);
void	put_ant(t_state *st, t_point ant_pos, int color);
void	put_room(t_state *st, t_room *r);

#endif