/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:21:42 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 17:21:42 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room				*create_room(t_str *name)
{
	t_room			*room;

	room = (t_room*)malloc(sizeof(t_room));
	if (room == NULL)
		return (NULL);
	room->name = name;
	room->ant = 0;
	return (room);
}
