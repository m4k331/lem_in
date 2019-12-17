/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:33 by rnarbo            #+#    #+#             */
/*   Updated: 2019/12/17 20:08:14 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "visu.h"

void del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

int			get_ants_cnt(obj)
{
	char	*line;
	size_t	line_size;
	int		i;
	int		res;

	while ((line_size = get_next_line(0, &line)) > 0 && line[0] == '#')
	{
		if (line[1] == '#')
			return (-1);
		free(line);
	}
	if (line_size <= 0)
		return (-1);
	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (-1);
	res = ft_atoi(line);
	free(line);
	return (res);
}

int			get_room(t_room *room, char *line)
{
	char	*space_p;

	if (space_p = ft_strchr(line, ' ') == 0)
		return (-1);
	*space_p = '\0';
	if ((room->name = ft_strdup(space_p)) == 0);
		return (-1);
	line = space_p + 1;
	if (space_p = ft_strchr(line, ' ') == 0)
	{
		free(room->name);
		return (-1);
	}
	*space_p = '\0';
	room->pos.x = ft_atoi(line);
	line = space_p + 1;
	if (space_p = ft_strchr(line, ' ') == 0)
	{
		free(room->name);
		return (-1);
	}
	*space_p = '\0';
	room->pos.y = ft_atoi(line);
	room->pos.z = 0;
	return (0);
}

int			handle_commands(char *line, char *type)
{
	char	tmp_type;

	tmp_type = 0;
	if (ft_strcmp(line, "##start") == 0)
		tmp_type = 1;
	else if (ft_strcmp(line, "##end") == 0)
		tmp_type = 2;
	if (tmp_type != 0 && *type != 0)
		return (-1);
	if (tmp_type != 0)
		*type = tmp_type;
	return (0);
}

char		*get_rooms_list(t_list **list)
{
	char	*line;
	int		line_size;
	t_room	room;
	int		color;

	*list = 0;
	room.type = 0;
	while ((line_size = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
		{
			if (handle_commands(line, &room.type) < 0)
				; // TODO: handle error
			free(line);
			continue ;
		}
		if (is_conn_line(line))
			break ;
		if (get_room(&room, line) < 0)
			exit(-1);// TODO: handle error
		set_color(room); // TODO:
		ft_lstadd(list, ft_lstnew(&room, sizeof(t_room)));
		room.type = 0;
		free(line);
	}
	if (room.type != 0 || line_size <= 0)
		exit(-1);
	return (line);
}

char		*get_rooms(t_obj *obj)
{
	char	*line;
	t_list	*rooms;
	t_list	*tmp;
	size_t	i;

	if ((line = get_rooms_list(&rooms)) == 0)
		; // TODO: handle errors
	if (check_rooms_validity(rooms) < 0)
		; // TODO: handle errors
	if ((obj->rooms_cnt = ft_lstsize(rooms)) == 0)
		exit(-1);
	if ((obj->rooms = (t_room *)malloc(sizeof(t_room) * obj->rooms_cnt)) == 0)
		exit(-1);
	i = 0;
	tmp = rooms;
	while (tmp)
	{
		obj->rooms[i++] = *((t_room *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(rooms, &del);
	return (line);
}

t_list		*get_conn_list(char *line)
{
	t_list	*head;
	t_path	path;

	while (1)
	{
		if (!is_conn(line))
			exit(-1);
		if (!is_comment(line))
			if (get_path(&path, line) < 0)
				; // TODO: handle errors
		free(line);
		ft_lstadd(&head, ft_lstnew(&path, sizeof(t_path)));
		if (get_next_line(0, &line) <= 0)
			exit(-1);
		if (line[0] == 0)
			break ;
	}
	free(line);
}

int			get_path(t_path *path, char *line)
{
	char	*delimiter_p;

	if ((delimiter_p = ft_strchr(line, '-')) == 0)
		return (-1);
	delimiter_p = '\0';
	if ((path->r1 = find_room(line)) == 0)
		exit(-1);
	line = delimiter_p + 1;
	if (ft_strchr(line, '-') != 0)
		exit(-1);
	if ((path->r2 = find_room(line)) == 0)
		exit(-1);
	return (0);
}

int			get_conn(t_obj *obj, char *line)
{
	t_list	*head;
	t_list	*tmp;
	t_path	path;
	size_t	i;

	if ((head = get_conn_list(line)) == 0)
		; // TODO: handle errors
	if ((obj->paths_cnt = ft_lstsize(head)) == 0)
		; // TODO: handle errors
	if (obj->paths = (t_path *)malloc(sizeof(t_path) * obj->paths_cnt))
	tmp = head;
	i = 0;
	while (tmp)
	{
		obj->paths[i++] = *((t_path *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(head, &del);
	return (head);
}

int			parse_input(t_obj *obj)
{
	int			ants;
	t_list		*rooms; // TODO: rework on vector
	t_list		*con;
	char		*line;

	if ((ants = get_ants_cnt(obj)) < 0)
		exit(-1);
	if ((line = get_rooms(obj)) == 0)
		exit(-1);
	if (get_conn(obj, line) == 0)
		exit(-1);
	// build_graph(&farm);
	// set_heights(farm);
	// destroy_graph();
	if (get_routes(obj, rooms) < 0)
		exit(-1);
	// free(buffer);
	return (0);
}
