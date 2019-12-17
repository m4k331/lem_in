#include "get_next_line.h"
#include "libft.h"
#include "visu.h"

static char	*get_buffer(void)
{
	char	*buffer;
	char	*line;
	char	*tmp;
	size_t	buffer_len;
	size_t	gnl_ret;

	buffer = 0;
	buffer_len = 0;
	while ((gnl_ret = get_next_line(0, &line)) > 0) // FIXME: gnl must return len on success
	{
		buffer_len += gnl_ret;
		tmp = buffer;
		if ((buffer = (char *)malloc(buffer_len + 2)) == 0)
		{
			free(buffer);
			return (0);
		}
		strcpy(buffer, tmp);
		free(tmp);
		strcat(buffer, line);
		free(line);
		strcat(buffer, "\n");
	}
	return (buffer);
}

int			get_routes_cnt(t_obj *obj, char **buffer)
{
	char	*line;
	int		i = 0;

	while ((*buffer)[0] == '#'i)
	{
		if ((*buffer)[1] == '#')
			return (-1);
		if ((*buffer = ft_strchr(*buffer, '\n')) == 0)
			return (-1);
		else
			*buffer = *buffer + 1;
	}
	i = 0;
	while (ft_isdigit((*buffer)[i]))
		i++;
	if ((*buffer)[i] != '\n')
		return (-1);
	obj->routes_cnt = ft_atoi(*buffer);
	*buffer += i;
	return (0);
}

char		*next_str(char *buff)
{
	char	*str;

	if ((str = strchr(buff, '\n')) == 0)
		return (0);
	return (str + 1);
}

size_t		count_rooms(char *buff)
{
	char	*tmp;
	size_t	cnt;

	cnt = 0;
	while ((tmp = strchr(buff, '\n')) != 0)
	{
		tmp++;
		if (!tmp[0] || tmp[0] == '\n')
			break ;
		if (tmp[0] == '#')
			continue ;
		cnt++;
	}
	return (cnt);
}

t_room		get_room(char **buffer)
{
	t_room	room;
	char	*buff;

	ft_memset(&room, 0, sizeof(t_room));
	buff = *buffer;
	while (*buff)
	{
		if (buff[0] == '#' && buff[1] == '#')
		{
			room.color = 0xff00ff;
		}

	}
	return (room);
}

int			get_rooms(t_obj *obj, char **buffer)
{
	char	*line;
	int		i;

	if ((obj->rooms_cnt = count_rooms(char *buff)) < 2)
		exit(-1);
	if ((obj->rooms = (t_room *)malloc(obj->rooms_cnt * sizeof(t_room))) == 0)
		exit(-1);
	i = 0;
	while (i < obj->rooms_cnt)
	{
		obj->rooms[i] = get_room(buffer);
		i++;
	}
	return (0);
}

int			parse_input(t_obj *obj)
{
	char	*buffer;
	char	*cutted_buffer;
	size_t	ants;
	t_list	*rooms; // TODO: rework on vector

	if ((buffer = get_buffer()) == 0)
		exit(-1);
	cutted_buffer = buffer;
	if (get_routes_cnt(obj, &cutted_buffer) < 0)
		exit(-1);
	if (rooms = get_rooms(obj, &cutted_buffer) == 0)
		exit(-1);
	if (get_routes(obj, rooms, &cutted_buffer) < 0)
		exit(-1);
	free(buffer);
	return (0);
}
