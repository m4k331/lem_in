/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:45:39 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/06 22:52:55 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				convert_path_to_printable(t_path *path)
{
	t_node			**node;
	t_room			*room;

	path->printable = TRUE;
	path->rooms->iter = -1;
	node = ft_vnext_con(path->rooms);
	while (node)
	{
		room = create_room((*node)->name);
		if (room == NULL)
		{
			path->rooms->head = path->rooms->iter;
			return (FALSE);
		}
		ft_memcpy(ft_vcurr_con(path->rooms), &room, path->rooms->type_size);
		node = ft_vnext_con(path->rooms);
	}
	return(TRUE);
}

int8_t				print_short(int fd, t_vector *colors, t_flows *flows)
{
	t_path				**path;
	long				ants;
	long				len;

	ants = 0;
	len = 0;
	flows->max_flow->paths->iter = -1;
	path = ft_vnext_con(flows->max_flow->paths);
	while (path)
	{
		ants += (*path)->ants;
		if (len < (*path)->len_path)
			len = (*path)->len_path;
		if (convert_path_to_printable(*path) == FALSE)
			return (FALSE);
		path = ft_vnext_con(flows->max_flow->paths);
	}
	return (TRUE);
}
