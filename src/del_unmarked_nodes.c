/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_unmarked_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 00:44:36 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/26 01:08:11 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				del_unmarked_nodes(t_farm *farm)
{
	t_node			*node;

	farm->nodes->items->iter = -1;
	node = ft_dictnext_item(farm->nodes);
	while (node)
	{
		if ((node->marks & 1) == FALSE)
			ft_dictunset(farm->nodes, node->name->con, destroy_node);
		else
			node->marks ^= 1;
		node = ft_dictnext_item(farm->nodes);
	}
}
