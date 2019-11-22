/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:29:34 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 17:36:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

typedef struct		s_room
{
	t_str			name;
	long			ant;
	char			color[16];
}					t_room;

t_room				*create_room(t_str *name);
void				destroy_room(t_room **room);
void				add_ant_to_room(t_room *room, long ant);

#endif
