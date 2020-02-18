/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_traces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:40:12 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 04:19:17 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "parse.h"

static char		*get_buffer()
{
	int		gnl_ret;
	char	*buff;
	char	*line;
	char	*tmp;

	if ((buff = ft_strnew(1)) == 0)
		exit(-1);
	while ((gnl_ret = get_next_line(0, &line)) > 0)
	{
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
		exit(print_error("GNL error!"));
	return (buff);
}

static int		get_routes_cnt(char *buff)
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

static t_room	**get_route_n(t_obj *obj, char *buff, int n)
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
	while ((tmp = ft_strstr(tmp, lem)) != 0 && ++tmp)
		i++;
	if ((route = (t_room **)malloc(sizeof(t_room *) * (i + 2))) == 0)
		exit(-1);
	route[i + 1] = 0;
	route[0] = find_start(obj);
	i = 1;
	while ((buff = ft_strstr(buff, lem)) != 0)
	{
		buff += lem_len;
		if ((route[i++] = find_room(obj, buff)) == 0)
			exit(-1);
	}
	free(lem);
	return (route);
}

static void		set_trace(t_obj *obj, char *buff, int n)
{
	char	*lem;
	char	*tmp;
	t_room	*room;
	size_t	i;

	lem = lem_itoa(n);
	if ((tmp = ft_strstr(buff, lem)) == 0)
		exit(print_error("Ant's trace couldn't be found!"));
	tmp += ft_strlen(lem);
	if ((room = find_room(obj, tmp)) == 0)
		exit(print_error("No such room on input!"));
	i = -1;
	while (++i < obj->routes_cnt)
		if (obj->routes[i][1] == room)
			break;
	if (i == obj->routes_cnt)
		exit(print_error("Invalid route!")); // TODO: add route
	obj->ants_traces[n].route = i;
	obj->ants_traces[n].step = 0;
	while (tmp != buff)
		if (*tmp-- == '\n')
			obj->ants_traces[n].step++;
	free(lem);
}

int				get_traces(t_obj *obj)
{
	char	*buff;
	size_t	i;

	if ((buff = get_buffer()) == 0)
		exit(print_error("Zero routes found!"));
	if ((obj->routes_cnt = get_routes_cnt(buff)) == 0)
		exit(print_error("Zero routes found!"));
	if ((obj->routes = malloc(obj->routes_cnt * sizeof(int *))) == 0)
		exit(print_error("Memory allocation failed!"));
	if ((obj->ants_traces = malloc(obj->ants_cnt * sizeof(t_trace))) == 0)
		exit(print_error("Memory allocation failed!"));
	i = -1;
	while (++i < obj->routes_cnt)
	{
		obj->routes[i] = get_route_n(obj, buff, i);
		obj->ants_traces[i].route = i;
		obj->ants_traces[i].step = 0;
	}
	while (i < obj->ants_cnt)
	{
		set_trace(obj, buff, i);
		i++;
	}
	free(buff);
	return (0);
}
