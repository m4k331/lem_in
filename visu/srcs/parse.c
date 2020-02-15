/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:33 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 18:45:19 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "get_next_line.h"
#include "libft.h"
#include "visu.h"

void		del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

int			get_ants_cnt(t_obj *obj)
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

void		del4dict(t_room **room)
{
	free(*room);
}

int			set_heights(t_obj *obj)
{
	int	i;
	int	height;
	int flag;

	i = -1;
	while (++i < obj->cons_cnt)
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
	}
	height = 2;
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = -1;
		while (++i < obj->cons_cnt)
		{
			if (obj->cons[i].r1->pos.z - height < 0.1 &&
				obj->cons[i].r1->pos.z != 0 &&
				(obj->cons[i].r2->pos.z > 0.1 + height ||
				obj->cons[i].r2->pos.z == 0))
			{
				obj->cons[i].r2->pos.z = height + 1;
				flag = 1;
			} else
			if (obj->cons[i].r2->pos.z - height < 0.1 &&
				obj->cons[i].r2->pos.z != 0 &&
				(obj->cons[i].r1->pos.z > 0.1 + height ||
				obj->cons[i].r1->pos.z == 0))
			{
				obj->cons[i].r1->pos.z = height + 1;
				flag = 1;
			}
		}
		height++;
	}
}

int			check_routes_buffer(char *buffer)
{
	return (0);
}

int			colorize_conns(t_obj *obj)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < obj->routes_cnt && (k = 0) == 0)
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
	return (0);
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
	if (get_traces(obj) < 0)
		exit(-1);
	if (colorize_conns(obj) < 0)
		exit(-1);
	return (0);
}
