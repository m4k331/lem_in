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
	void			*raw_node;
	t_node			*node;

	farm->nodes->items->iter = -1;
	raw_node = ft_dictnext_item(farm->nodes);
	while (raw_node)
	{
		node = *(t_node**)raw_node;
		if (MARKED(node->marks) == FALSE)
			ft_dictunset(farm->nodes, node->name->con, destroy_node);
		else
			UNMARKING(node->marks);
		raw_node = ft_dictnext_item(farm->nodes);
	}
}
