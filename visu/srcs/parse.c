/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 15:29:00 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "get_next_line.h"
#include "libft.h"
#include "visu.h"

void del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

int			get_ants_cnt(t_obj *obj) // TODO:
{
	char	*line;
	ssize_t	line_size;
	int		i;
	int		res;

	while ((line_size = get_next_line(0, &line)) > 0 && line[0] == '#')
		free(line);
	if (line_size <= 0)
		exit(-1);
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
	room->pos.x = ft_atoi(line); // test digits
	line = space_p + 1;
	room->pos.y = ft_atoi(line);
	room->pos.z = 0;
	return (0);
}

int			handle_commands(char *line, char *type)
{
	char	tmp_type;

	tmp_type = ROOM_TYPE_REGULAR;
	if (ft_strcmp(line, "##start") == 0)
		tmp_type = ROOM_TYPE_START;
	else if (ft_strcmp(line, "##end") == 0)
		tmp_type = ROOM_TYPE_END;
	// if (tmp_type != ROOM_TYPE_REGULAR && *type != ROOM_TYPE_REGULAR)
	// 	return (-1);
	if (tmp_type != ROOM_TYPE_REGULAR)
		*type = tmp_type;
	return (0);
}

int is_room_line(char *line)
{
	char	*space_p;
	int		i;

	i = 0;
	if ((space_p = ft_strchr(line, ' ')) == 0)
		return (0);
	line = space_p + 1;
	if ((space_p = ft_strchr(line, ' ')) == 0)
		return (0);
	while (line != space_p)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	line++;
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	return (1);
}

void set_color(t_room *room)
{
	if (room->type == ROOM_TYPE_START)
		room->color = START_ROOM_COLOR;
	else if (room->type == ROOM_TYPE_END)
		room->color = END_ROOM_COLOR;
	else
		room->color = REGULAR_ROOM_COLOR;
}

// char		*get_rooms_list(t_list **list)
// {
// 	char	*line;
// 	int		line_size;
// 	t_room	room;
// 	int		color;

// 	*list = 0;
// 	room.type = 0;
// 	while ((line_size = get_next_line(0, &line)) > 0)
// 	{
// 		if (line[0] == '#')
// 		{
// 			if (handle_commands(line, &room.type) < 0)
// 				exit(print_error("Multiple commands for one room!")); // TODO: handle error
// 			free(line);
// 			continue ;
// 		}
// 		if (!is_room_line(line))
// 			break ;
// 		if (get_room(&room, line) < 0)
// 			exit(print_error("Unable to get some room!"));// TODO: handle error
// 		set_color(&room);
// 		ft_lstadd(list, ft_lstnew(&room, sizeof(t_room)));
// 		room.type = 0;
// 		free(line);
// 	}
// 	if (room.type != 0 || line_size <= 0)
// 		exit(print_error(line_size <= 0 ? "GNL error" : "Command without room!"));
// 	return (line);
// }

// char		*get_rooms_dict(t_dict *dict)
// {
// 	char	*line;
// 	int		line_size;
// 	t_room	room;
// 	t_room	*to_dict;
// 	int		color;

// 	dict = ft_dictnew(4096);
// 	room.type = 0;
// 	while ((line_size = get_next_line(0, &line)) > 0)
// 	{
// 		if (line[0] == '#')
// 			if (handle_commands(line, &room.type) < 0)
// 				exit(print_error("Multiple commands for one room!")); // TODO: handle error
// 		else
// 		{
// 			if (!is_room_line(line))
// 				break ;
// 			if (get_room(&room, line) < 0)
// 				exit(print_error("Unable to get some room!"));// TODO: handle error
// 			if (ft_dictget(dict, room.name) != 0)
// 				exit(print_error("Some rooms are not valid!"));
// 			set_color(&room);
// 			if ((to_dict = (t_room *)malloc(sizeof(t_room))) == 0)
// 				exit(-1);
// 			*to_dict = room;
// 			ft_dictset(dict, room.name, to_dict);
// 			room.type = 0;
// 		}
// 		free(line);
// 	}
// 	if (room.type != 0 || line_size <= 0)
// 		exit(print_error(line_size <= 0 ? "GNL error" : "Command without room!"));
// 	return (line);
// }

char		*get_rooms_dict(t_dict **dict)
{
	char	*line;
	int		line_size;
	t_room	room;
	t_room	*to_dict;
	int		has_start_end;

	*dict = ft_dictnew(32);
	room.type = 0;
	has_start_end = 0;
	while ((line_size = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
		{
			if (handle_commands(line, &room.type) < 0)
				exit(print_error("Multiple commands for one room!")); // TODO: handle error
			free(line);
			continue ;
		}
		if (!is_room_line(line))
			break ;
		if (get_room(&room, line) < 0)
			exit(print_error("Unable to get some room!"));// TODO: handle error
		if (ft_dictget(*dict, room.name) != 0)
			exit(print_error("Some rooms are not valid!"));
		set_color(&room);
		if ((to_dict = (t_room *)malloc(sizeof(t_room))) == 0)
			exit(-1);
		*to_dict = room;
		ft_dictset(*dict, room.name, to_dict);
		if (has_start_end & room.type)
			exit(print_error("Rooms must have only one start / end!"));
		else
			has_start_end |= room.type;
		room.type = 0;
		free(line);
	}
	if (!((has_start_end & ROOM_TYPE_END) && (has_start_end & ROOM_TYPE_START)))
		exit(print_error("No start / end command found!"));
	if (room.type != 0 || line_size <= 0)
		exit(print_error(line_size <= 0 ? "GNL error" : "Command without room!"));
	return (line);
}

// int check_rooms_validity(t_dict *dict) // TODO: Check same namings
// {
// 	t_list	*tmp;
// 	char	start_end;

// 	start_end = 0;
// 	while (rooms)
// 	{
// 		if (((t_room *)rooms->content)->type == 1)
// 		{
// 			if (start_end & 1)
// 				return (-1);
// 			else 
// 				start_end |= 1;
// 		}
// 		if (((t_room *)rooms->content)->type == 2)
// 		{
// 			if (start_end & 2)
// 				return (-1);
// 			else 
// 				start_end |= 2;
// 		}
// 		// tmp = rooms->next;
// 		// while (tmp)
// 		// {
// 		// 	if (strcmp(((t_room *)tmp->content)->name, ((t_room *)rooms->content)->name) == 0)
// 		// 		return (-1);
// 		// 	tmp = tmp->next;
// 		// }
// 		rooms = rooms->next;
// 	}
// 	if (start_end != 3)
// 		return (-1);
// 	return (0);
// }

int map(t_room *room)
{
	static int i = 0;

	printf("%d\n", ++i);
	return 1;
}

void del4dict(t_room **room)
{
	printf("%p\n", *room);
	printf("%s\n", (*room)->name);
	printf("(%f %f %f)\n", (*room)->pos.x, (*room)->pos.y, (*room)->pos.z);
	free(*room);
}

t_dict	*rooms_dict2array(t_obj *obj, t_dict *rooms)
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
		ft_dictset(rooms, obj->rooms[i].name, obj->rooms + i++);
	return (rooms);

}

int			is_comment(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
			return (-1);
		else
			return (1);
	}
	else
		return (0);
}

int			set_conn_rooms(t_conn *conn, t_dict *rooms, char *line)
{
	char	*dash_p;
	int		i;

	if ((dash_p = ft_strchr(line, '-')) == 0)
		return (-1);
	*dash_p = '\0';
	if ((conn->r1 = ft_dictget(rooms, line)) == 0)
		return (-1);
	line = dash_p + 1;
	if ((conn->r2 = ft_dictget(rooms, line)) == 0)
		return (-1);
	return 0;
	// while (i < obj->rooms_cnt) // TODO: remove duplicates
	// {
	// 	if (ft_strcmp(obj->rooms[i].name, line) == 0)
	// 	{
	// 		conn->r1 = obj->rooms + i;
	// 		break ;
	// 	}
	// 	i++;
	// }
	// if (i == obj->rooms_cnt)
	// 	return (-1);
	// while (i < obj->rooms_cnt)
	// {
	// 	if (ft_strcmp(obj->rooms[i].name, line) == 0)
	// 	{
	// 		conn->r2 = obj->rooms + i;
	// 		break ;
	// 	}
	// 	i++;
	// }
	// if (i == obj->rooms_cnt)
	// 	return (-1);
	// return (0);
}

int			is_conn(char *line)
{
	if (line[0] == 'L' || ft_strchr(line, '-') == 0)
		return (0);
	return (1);
}

void	get_conn_vector(t_vector **conns, t_dict *rooms, char *line)
{
	t_conn	conn;
	int		comment;
	int		i = 1;

	*conns = ft_vnew(1024 * sizeof(t_conn), sizeof(t_conn));
	while (1)
	{
		if ((comment = is_comment(line)) != 1)
		{
			if (!is_conn(line))
				break ;
			else if (comment == -1)
				exit(print_error("Command found in connections block!"));
			set_conn_rooms(&conn, rooms, line);
			// printf("line: %i\n", i++);
			ft_vpush_back(*conns, &conn, sizeof(t_conn));
			// i++;
			// ft_lstadd(head, ft_lstnew(&conn, sizeof(t_conn)));
		}
		free(line);
		if (get_next_line(0, &line) <= 0)
		{
			break ;
			exit(-1); // gnl return value == 0 if str is ""
		}
	}
	printf("OK\n");
	free(line);
}

// void	get_conn_list(t_list **head, t_obj *obj, char *line)
// {
// 	t_conn	conn;
// 	int		comment;
// 	int		i = 0;

// 	while (1)
// 	{
// 		if ((comment = is_comment(line)) != 1)
// 		{
// 			if (!is_conn(line))
// 				break ;
// 			else if (comment == -1)
// 				exit(print_error("Command found in connections block!"));
// 			set_conn_rooms(obj, &conn, line);
// 			i++;
// 			ft_lstadd(head, ft_lstnew(&conn, sizeof(t_conn)));
// 		}
// 		free(line);
// 		if (get_next_line(0, &line) <= 0)
// 		{
// 			break ;
// 			exit(-1); // gnl return value == 0 if str is ""
// 		}
// 	}
// 	free(line);
// }

void print_list(t_list *head)
{
	while (head)
	{
		printf("(%p)->", head);
		head = head->next;
	}
	printf("(null)\n");
}

int			remove_sim_room_conn(t_list **head)
{
	t_list *tmp;
	t_list *tmp_prev;

	tmp = head;
	tmp_prev = 0;
	while (tmp)
	{
		if (((t_conn *)tmp->content)->r1 == ((t_conn *)tmp->content)->r2)
		{
			if (tmp == *head)
				*head = tmp->next;
			else
				tmp_prev->next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = (tmp_prev != 0 ? tmp_prev : *head);
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

// void		remove_duplicates(t_list *head)
// {
// 	t_list	*tmp;
// 	t_list	*tmp_to_rm;

// 	while (head && head->next)
// 	{
// 		tmp_to_rm = head;
// 		tmp = head->next;
// 		while (tmp)
// 		{
// 			if ((((t_conn *)tmp->content)->r1 == ((t_conn *)head->content)->r1 && 
// 				((t_conn *)tmp->content)->r2 == ((t_conn *)head->content)->r2) ||
// 				(((t_conn *)tmp->content)->r2 == ((t_conn *)head->content)->r1 && 
// 				((t_conn *)tmp->content)->r1 == ((t_conn *)head->content)->r2))
// 			{
// 				free(tmp->content);
// 				tmp_to_rm->next = tmp->next;
// 				free(tmp);
// 				tmp = tmp_to_rm->next;
// 				continue ;
// 			}
// 			tmp_to_rm = tmp;
// 			tmp = tmp->next;
// 		}
// 		head = head->next;
// 	}
// }
void		print_conns(t_obj *obj);

void	get_conn(t_obj *obj, t_dict *rooms, char *line)
{
	t_vector	*conns;
	t_list	*tmp;
	t_conn	path;
	size_t	i;

	// head = 0;
	get_conn_vector(&conns, rooms, line);
	// printf("OKx2\n");
	// printf("cUsize: %d\n", ft_vunused_size(conns));
	// ft_v
	// remove_sim_room_conn(head);
	// remove_duplicates(head);
	if ((obj->cons_cnt = conns->head) == 0)
		exit(print_error("Zero conns found!"));
	printf("obj->cons_cnt: %d\n", obj->cons_cnt);
	// if ((obj->cons_cnt = ft_lstsize(head)) == 0)
		; // TODO: handle errors
	if ((obj->cons = (t_conn *)malloc(sizeof(t_conn) * obj->cons_cnt)) == 0)
		exit(-1);
	i = 0;
	while (i < obj->cons_cnt)
	{
		obj->cons[i] = *(t_conn *)ft_vpop_back(conns);
		printf("%d (%s-%s)\n", i, obj->cons[i].r1->name, obj->cons[i].r2->name);
		// obj->cons[i] = *((t_conn *)tmp->content);
		obj->cons[i++].color = CONN_COLOR;
		// tmp = tmp->next;
	}
	ft_vdel(&conns);
	// print_conns(obj);
	// ft_lstdel(&head, &del);
}

void		print_rooms(t_obj *obj)
{
	// TODO: delete

	t_room	*room = obj->rooms;
	int i = 0;

	while (i < obj->rooms_cnt)
	{
		printf("room #%d\n", i);
		printf("\tname: \'%s\'\n", room[i].name);
		printf("\tpos (%.1f, %.1f, %.1f)\n", room[i].pos.x, room[i].pos.y, room[i].pos.z);
		printf("\ttype: %s\n", (room[i].type == 0) ? "regular" : (room[i].type == 1) ? "start" : (room[i].type == 2) ? "end" : "I'm fucked up.");
		printf("\tcolor %#x\n\n", room[i].color);
		i++;
	}
}

void		print_conns(t_obj *obj)
{
	t_conn	*conn = obj->cons;
	int i = 0;

	printf("conn_cnt: %d\n", obj->cons_cnt);
	while (i < obj->cons_cnt)
	{
		printf("conn #%d\n", i);
		printf("\t%s-%s\n", conn[i].r1->name, conn[i].r2->name);
		i++;
	}
}

int			set_heights(t_obj *obj)
{
	int	i;
	int	height;
	int flag;

	i = 0;
	while (i < obj->cons_cnt)
	{
		if (obj->cons[i].r1->type == 1 || obj->cons[i].r1->type == 2)
		{
			obj->cons[i].r1->pos.z = 1;
			obj->cons[i].r2->pos.z = 2;
		}
		if (obj->cons[i].r2->type == 1 || obj->cons[i].r2->type == 2)
		{
			obj->cons[i].r1->pos.z = 2;
			obj->cons[i].r2->pos.z = 1;
		}
		i++;
	}
	height = 2;
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < obj->cons_cnt)
		{
			if (obj->cons[i].r1->pos.z - height < 0.1 && obj->cons[i].r1->pos.z != 0 &&
				(obj->cons[i].r2->pos.z > 0.1 + height || obj->cons[i].r2->pos.z == 0))
			{
				obj->cons[i].r2->pos.z = height + 1;
				flag = 1;
			}
			if (obj->cons[i].r2->pos.z - height < 0.1 && obj->cons[i].r2->pos.z != 0 &&
				(obj->cons[i].r1->pos.z > 0.1 + height || obj->cons[i].r1->pos.z == 0))
			{
				obj->cons[i].r1->pos.z = height + 1;
				flag = 1;
			}
			i++;
		}
		height++;
	}
}

char		*get_buffer()
{
	int		gnl_ret;
	char	*buff;
	char	*line;
	char	*tmp;

	buff = ft_strnew(1);
	while ((gnl_ret = get_next_line(0, &line)) > 0)
	{
		// if (line[0] == '#')
		// {
		// 	free(line);
		// 	continue ;
		// }
		if ((tmp = ft_strjoin(line, "\n")) == 0)
			exit(-1);
		free(line);
		line = tmp;
		tmp = buff;
		if ((buff = ft_strjoin(buff, line)) == 0)
			exit(-1);
		free(line);
		free(tmp);
	}
	free(line);
	if (gnl_ret < 0)
		exit(-1);
	return (buff);
}

int			check_routes_buffer(char *buffer)
{
	return 0;
}

int colorize_conns(t_obj *obj)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < obj->routes_cnt)
	{
		k = 0;
		while (obj->routes[i][k] && obj->routes[i][k + 1])
		{
			j = -1;
			while (++j < obj->cons_cnt)
				if ((obj->cons[j].r1 == obj->routes[i][k] &&
						obj->cons[j].r2 == obj->routes[i][k + 1]) ||
					(obj->cons[j].r2 == obj->routes[i][k] &&
						obj->cons[j].r1 == obj->routes[i][k + 1]))
				{
					obj->cons[j].color = TRACE_COLOR;
					break ;
				}
			if (j == obj->cons_cnt)
				return (-1);
			k++;
		}
	}
	return (0);
}

int			get_routes_cnt(char *buff)
{
	int cnt;

	cnt = 0;
	while (*buff && *buff != '\n')
	{
		if (*buff == '-')
			cnt++;
		buff++;
	}
	if (!*buff || ft_strchr(buff + 1, '\n') == 0)
		return (cnt == 0 ? 0 : 1);
	return (cnt);
}

void expand_routes_table_for_idiot_user_with_damaged_brain();

char		*lem_itoa(int n)
{
	char *lem;
	char *tmp;
	int i_len;

	if ((tmp = ft_itoa(n + 1)) == 0)
		exit(-1);
	i_len = ft_strlen(tmp);
	if ((lem = (char *)malloc(i_len + 3)) == 0)
		exit(-1);
	ft_memmove(lem + 1, tmp, i_len);
	free(tmp);
	lem[0] = 'L';
	lem[i_len + 1] = '-';
	lem[i_len + 2] = '\0';
	return (lem);
}

t_room	*find_room(t_obj *obj, char *name)
{
	int		i;
	char	*str;
	char	*n_p;
	int		cmp;

	i = 0;
	while (i < obj->rooms_cnt)
	{
		str = obj->rooms[i].name;
		n_p = name;
		while (*str && *n_p && *str == *n_p)
		{
			str++;
			n_p++;
		}
		if (!*str && (*n_p == ' ' || *n_p == '\n' || *n_p == '\0'))
			return (obj->rooms + i);
		i++;
	}
	return (0);
}

t_room	*find_start(t_obj *obj)
{
	int i;

	i = 0;
	while (i < obj->rooms_cnt)
	{
		if (obj->rooms[i].type == 1)
			return (obj->rooms + i);
		i++;
	}
	return (0);
}

// start-end
t_room		**get_route_n(t_obj *obj, char *buff, int n)
{
	int		i;
	char	*lem;
	int		lem_len;
	char	*tmp;
	t_room	**route;
	
	lem = lem_itoa(n);
	lem_len = ft_strlen(lem);
	tmp = buff;
	i = 0;
	while ((tmp = ft_strstr(tmp, lem)) != 0)
	{
		i++;
		tmp++;
	}
	route = (t_room **)malloc(sizeof(t_room *) * (i + 2));
	route[i + 1] = 0;
	route[0] = find_start(obj); // del
	// start
	i = 1; // fix
	while ((buff = ft_strstr(buff, lem)) != 0)
	{
		buff += lem_len;
		route[i] = find_room(obj, buff);
		i++;
	}
	free(lem);
	return (route);
}

void	set_trace(t_obj *obj, char *buff, int n)
{
	char	*lem;
	char	*tmp;
	t_room	*room;
	int i;

	lem = lem_itoa(n);
	tmp = ft_strstr(buff, lem);
	tmp += ft_strlen(lem);
	room = find_room(obj, tmp);
	i = 0;
	printf("trace %d\n", n);
	while (i < obj->routes_cnt)
	{
		if (obj->routes[i][1] == room)
			break;
		i++;
	}
	obj->ants_traces[n].route = i;
	obj->ants_traces[n].step = 0;
	printf("trace\n");
	while (tmp != buff)
	{
		if (*tmp == '\n')
			obj->ants_traces[n].step++;
		tmp--;
	}
	printf("trace with route #%d\n", obj->ants_traces[n].route);
	free(lem);
}

int			get_traces(t_obj *obj)
{
	char	*buff;
	int		i;

	if ((buff = get_buffer()) == 0)
		exit(-1);
	if (check_routes_buffer(buff) < 0)
		exit (-1);
	obj->routes_cnt = get_routes_cnt(buff);
	if ((obj->routes = malloc(obj->routes_cnt * sizeof(int *))) == 0)
		exit(-1);
	if ((obj->ants_traces = malloc(obj->ants_cnt * sizeof(t_trace))))
	i = 0;
	while (i < obj->routes_cnt)
	{
		obj->routes[i] = get_route_n(obj, buff, i);
		obj->ants_traces[i].route = i;
		obj->ants_traces[i].step = 0;
		i++;
	}
	while (i < obj->ants_cnt)
	{
		set_trace(obj, buff, i);
		i++;
	}
	free(buff);
	return 0;
}

int			parse_input(t_obj *obj)
{
	int			ants;
	t_dict		*rooms;
	t_list		*con;
	char		*line;

	if ((obj->ants_cnt = get_ants_cnt(obj)) < 0)
		exit(print_error("Invalid ants count!"));
	if ((line = get_rooms_dict(&rooms)) == 0)
		exit(print_error(""));
	rooms = rooms_dict2array(obj, rooms);
	get_conn(obj, rooms, line);
	ft_dictdel(&rooms, 0);
	set_heights(obj);
	if (get_traces(obj) < 0) // TODO:
		exit(-1);
	if (colorize_conns(obj) < 0)
		exit(-1);
	return (0);
}
