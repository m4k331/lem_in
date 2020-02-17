/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 02:16:28 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "get_next_line.h"
#include "libft.h"
#include "visu.h"

static int	get_ants_cnt()
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

static int	set_height(t_room *r1, t_room *r2, int height)
{
	if (r1->pos.z - height < 0.1 && r1->pos.z != 0 &&
		(r2->pos.z > 0.1 + height || r2->pos.z == 0))
	{
		r2->pos.z = height + 1;
		return (1);
	}
	return (0);
}

static void	set_heights(t_obj *obj)
{
	size_t	i;
	int		height;
	int		flag;

	height = 1;
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = -1;
		while (++i < obj->cons_cnt)
		{
			flag |= set_height(obj->cons[i].r1, obj->cons[i].r2, height);
			flag |= set_height(obj->cons[i].r2, obj->cons[i].r1, height);
		}
		height++;
	}
}

static int	colorize_conns(t_obj *obj)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	while (++i < obj->routes_cnt && (k = 0) == 0)
	{
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

int			parse_input(t_obj *obj)
{
	t_dict		*rooms;
	char		*line;

	if ((obj->ants_cnt = get_ants_cnt()) < 0)
		exit(print_error("Invalid ants count!"));
	line = get_rooms_dict(&rooms);
	check_rooms_dict(rooms);
	rooms = rooms_dict2array(obj, rooms);
	get_conn(obj, rooms, line);
	ft_dictdel(&rooms, 0);
	set_heights(obj);
	if (get_traces(obj) < 0)
		exit(-1);
	if (colorize_conns(obj) < 0)
		exit(-1);
	return (0);
}
