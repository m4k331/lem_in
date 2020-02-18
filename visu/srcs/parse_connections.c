/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_connections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:37:44 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 04:18:21 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "parse.h"

static int	is_comment(char *line)
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

static int	set_conn_rooms(t_conn *conn, t_dict *rooms, char *line)
{
	char	*dash_p;

	if ((dash_p = ft_strchr(line, '-')) == 0)
		return (-1);
	*dash_p = '\0';
	if ((conn->r1 = ft_dictget(rooms, line)) == 0)
		return (-1);
	line = dash_p + 1;
	if ((conn->r2 = ft_dictget(rooms, line)) == 0)
		return (-1);
	return (0);
}

static void	get_conn_vector(t_vector **conns, t_dict *rooms, char *line)
{
	t_conn	conn;
	int		comment;
	int		i;

	*conns = ft_vnew(1024 * sizeof(t_conn), sizeof(t_conn));
	i = 1;
	while (1)
	{
		if ((comment = is_comment(line)) != 1)
		{
			if (line[0] == 'L' || ft_strchr(line, '-') == 0)
				break ;
			else if (comment == -1)
				exit(print_error("Command found in connections block!"));
			if (set_conn_rooms(&conn, rooms, line) == -1)
				exit(print_error("Invalid connection!"));
			ft_vpush_back(*conns, &conn, sizeof(t_conn));
		}
		free(line);
		if (get_next_line(0, &line) <= 0)
			break ;
	}
	if (line == 0)
		exit(print_error("No routes found!"));
	free(line);
}

// static int	remove_sim_room_conn(t_vector *conns)
// {
// 	size_t i;
// 	size_t j;
// 	t_conn *conn1;
// 	t_conn *conn2;

// 	i = 0;
// 	while ((conn1 = ft_vat(conns, i)) != 0)
// 	{
// 		j = i + 1;
// 		while ((conn2 = ft_vat(conns, j)) != 0)
// 		{
// 			if (conn1->r1 == conn2->r1 &&
// 				conn1->r2 == conn2->r2 ||
// 				conn1->r1 == conn2->r2 &&
// 				conn1->r2 == conn2->r1)
// 				ft_vpop_at(conns, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void		get_conn(t_obj *obj, t_dict *rooms, char *line)
{
	t_vector	*conns;
	size_t	i;

	get_conn_vector(&conns, rooms, line);
	// remove_sim_room_conn(conns);
	if ((obj->cons_cnt = conns->head) == 0)
		exit(print_error("Zero conns found!"));
	if ((obj->cons = (t_conn *)malloc(sizeof(t_conn) * obj->cons_cnt)) == 0)
		exit(-1);
	i = 0;
	while (i < obj->cons_cnt)
	{
		obj->cons[i] = *(t_conn *)ft_vpop_back(conns);
		obj->cons[i++].color = CONN_COLOR;
	}
	ft_vdel(&conns);
}
