/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:23:58 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 15:25:48 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_H
# define FLOW_H

typedef struct		s_flow
{
	t_vector		*paths;
	long			steps;
}					t_flow;

typedef struct		s_path
{
	t_vector		*rooms;
	long			ants;
	int				printable;
}					t_path;

typedef struct		s_room
{
	t_str			*name;
	long			ant;
	char			color[16];
}					t_room;

t_room				*create_room(t_str *name);
void				destroy_room(t_room **room);
void				add_ant_to_room(t_room *room, long ant);

#endif
