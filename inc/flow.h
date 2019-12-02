/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:23:58 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 17:13:24 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_H
# define FLOW_H

# define INITIAL_FLOWS 256

typedef struct		s_flows
{
	t_vector		*flows;
	long			steps;
}					t_flows;

void				destroy_flows(t_flows **flows);

typedef struct		s_flow
{
	t_vector		*paths;
	long			steps;
}					t_flow;

typedef struct		s_path
{
	t_vector		*rooms;
	long			ants;
	int8_t			printable;
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