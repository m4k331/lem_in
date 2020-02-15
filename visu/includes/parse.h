/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:30:25 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 18:33:53 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define ROOM_TYPE_REGULAR	0
# define ROOM_TYPE_START	1
# define ROOM_TYPE_END		2

#include "visu.h"

int			get_room(t_room *room, char *line);
t_dict		*rooms_dict2array(t_obj *obj, t_dict *rooms);
int			is_room_line(char *line);
char		*get_rooms_dict(t_dict **dict);
void		get_conn(t_obj *obj, t_dict *rooms, char *line);
int			remove_sim_room_conn(t_list **head);
void		get_conn_vector(t_vector **conns, t_dict *rooms, char *line);
int			is_conn(char *line);
int			set_conn_rooms(t_conn *conn, t_dict *rooms, char *line);
int			is_comment(char *line);
char		*lem_itoa(int n);
int			get_routes_cnt(char *buff);
t_room	*find_room(t_obj *obj, char *name);
t_room	*find_start(t_obj *obj);
t_room		**get_route_n(t_obj *obj, char *buff, int n);
void	set_trace(t_obj *obj, char *buff, int n);
int			get_traces(t_obj *obj);

#endif
