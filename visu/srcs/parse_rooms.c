/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:33:30 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 01:15:11 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "parse.h"

static int	get_room(t_room *room, char *line)
{
	char	*space_p;

	if ((space_p = ft_strchr(line, ' ')) == 0 ||
		space_p == line || line[0] == 'L')
		return (-1);
	*space_p = '\0';
	if ((room->name = strdup(line)) == 0)
		return (-1);
	line = space_p + 1;
	if ((space_p = ft_strchr(line, ' ')) == 0)
	{
		free(room->name);
		return (-1);
	}
	*space_p = '\0';
	room->pos.x = ft_atoi(line);
	line = space_p + 1;
	room->pos.y = ft_atoi(line);
	room->color = REGULAR_ROOM_COLOR;
	if (room->type == ROOM_TYPE_START)
		room->color = START_ROOM_COLOR;
	else if (room->type == ROOM_TYPE_END)
		room->color = END_ROOM_COLOR;
	room->pos.z = room->type ? 1 : 0;
	return (0);
}

static void	add_room2dict(t_dict *dict, t_room *room, char *line)
{
	t_room *to_dict;
	
	if (get_room(room, line) < 0)
		exit(print_error("Unable to get some room!"));
	if (ft_dictget(dict, room->name) != 0)
		exit(print_error("Some rooms are not valid!"));
	if ((to_dict = (t_room *)malloc(sizeof(t_room))) == 0)
		exit(-1);
	*to_dict = *room;
	ft_dictset(dict, room->name, to_dict);
}

void		check_rooms_dict(t_dict *dict)
{
	t_room *room;
	char has_start_end;

	has_start_end = 0;
	dict->items->iter = -1;
	while ((room = ft_dictnext_item(dict)) != 0)
	{
		if (has_start_end & room->type & !ROOM_TYPE_REGULAR)
			exit(print_error("Rooms must have only 1 start / end!"));
		has_start_end |= room->type;
	}
	if ((has_start_end & ROOM_TYPE_START) &&
		(has_start_end & ROOM_TYPE_END))
		return ;
	exit(print_error("No start / end command found!"));
}

char		*get_rooms_dict(t_dict **dict)
{
	char	*line;
	int		line_size;
	t_room	room;

	if ((*dict = ft_dictnew(32)) == 0)
		exit(print_error("Dict allocation failed!"));
	room.type = 0;
	while ((line_size = get_next_line(0, &line)) > 0)
	{
		if (!handle_commands(line, &room.type))
		{
			if (!is_room_line(line))
				break ;
			add_room2dict(*dict, &room, line);
			room.type = 0;
		}
		free(line);
	}
	if (line_size <= 0)
		exit(print_error("GNL error"));
	if (room.type != 0)
		exit(print_error("Command without room!"));
	return (line);
}

t_dict		*rooms_dict2array(t_obj *obj, t_dict *rooms)
{
	size_t	i;

	rooms->items->iter = -1;
	while (ft_dictnext_item(rooms))
		obj->rooms_cnt++;
	if ((obj->rooms = (t_room *)malloc(sizeof(t_room) * obj->rooms_cnt)) == 0)
		exit(print_error("Failed to allocate rooms array!"));
	i = 0;
	rooms->items->iter = -1;
	while (i < obj->rooms_cnt)
		obj->rooms[i++] = *(t_room *)ft_dictnext_item(rooms);
	ft_dictdel(&rooms, del4dict);
	rooms = ft_dictnew(32);
	i = 0;
	while (i < obj->rooms_cnt)
		if (ft_dictset(rooms, obj->rooms[i].name, obj->rooms + i++) == 0)
			exit(-1);
	return (rooms);
}
