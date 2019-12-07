/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:37:01 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 15:38:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long				shift_ants(t_path *path, t_vector *colors, long ant)
{
	t_room			**room;
	long			prev;
	long			curr;

	path->rooms->iter = 0;
	room = ft_vnext_con(path->rooms);
	prev = (*room)->ant;
	add_ant_to_room(*room, colors, ant);
	room = ft_vnext_con(path->rooms);
	while (room)
	{
		curr = (*room)->ant;
		add_ant_to_room(*room, colors, prev);
		prev = curr;
		room = ft_vnext_con(path->rooms);
	}
	return ((prev != 0 ? 1 : 0));
}
