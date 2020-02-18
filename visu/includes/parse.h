/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:30:25 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 02:39:26 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define ROOM_TYPE_REGULAR	0
# define ROOM_TYPE_START	1
# define ROOM_TYPE_END		2

#include "visu.h"

int			parse_input(t_obj *obj);

t_dict		*rooms_dict2array(t_obj *obj, t_dict *rooms);
char		*get_rooms_dict(t_dict **dict);
void		get_conn(t_obj *obj, t_dict *rooms, char *line);
int			get_traces(t_obj *obj);
void		check_rooms_dict(t_dict *dict);

void		del4dict(t_room **room);
void		del(void *content, size_t content_size);

/*
** Utils
*/

int			is_room_line(char *line);
int			is_conn(char *line);
int			handle_commands(char *line, char *type);
char		*lem_itoa(int n);
t_room		*find_room(t_obj *obj, char *name);
t_room		*find_start(t_obj *obj);

#endif
