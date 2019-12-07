/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:23:58 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 21:59:12 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_H
# define FLOW_H

# define COLOR_LN      11
# define INITIAL_FLOWS 128U

typedef struct		s_flow
{
	t_vector		*paths;
	long			steps;
}					t_flow;

t_flow				*create_flow(void);
int					destroy_flow(void *f);

typedef struct		s_flows
{
	t_vector		*flows;
	t_flow			*max_flow;
	long			best_steps;
}					t_flows;

void				destroy_flows(t_flows **flows);

typedef struct		s_path
{
	t_vector		*rooms;
	long			ants;
	long			len_path;
	int8_t			printable;
}					t_path;

t_path				*create_path(void);
int					destroy_path(void *p);

typedef struct		s_room
{
	t_str			*name;
	long			ant;
	char			color[COLOR_LN];
}					t_room;

t_room				*create_room(t_str *name);
int					destroy_room(void *room);
void				add_ant_to_room(t_room *room, t_vector *colors, long ant);

#endif
