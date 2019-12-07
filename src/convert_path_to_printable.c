/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_path_to_printable.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:48:29 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 17:48:29 by ahugh            ###   ########.fr       */
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