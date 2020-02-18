/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 01:03:21 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 04:21:02 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "parse.h"

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


t_room	*find_room(t_obj *obj, char *name) // dict
{
	size_t	i;
	char	*str;
	char	*n_p;

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
	size_t i;

	i = 0;
	while (i < obj->rooms_cnt)
	{
		if (obj->rooms[i].type == 1)
			return (obj->rooms + i);
		i++;
	}
	return (0);
}

int			handle_commands(char *line, char *type)
{
	char	tmp_type;

	if (line[0] != '#')
		return (0);
	if (line[1] != '#')
		return (1);
	tmp_type = ROOM_TYPE_REGULAR;
	if (ft_strcmp(line, "##start") == 0)
		tmp_type = ROOM_TYPE_START;
	else if (ft_strcmp(line, "##end") == 0)
		tmp_type = ROOM_TYPE_END;
	if (tmp_type != ROOM_TYPE_REGULAR)
		*type = tmp_type;
	return (1);
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
