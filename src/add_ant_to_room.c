/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ant_to_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:22:43 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 15:29:46 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				add_ant_to_room(t_room *room, t_vector *colors, long ant)
{
	room->ant = ant;
	if (colors)
		ft_memcpy(room->color, ft_vat(colors, ant % MC), COLOR_LN);
}
