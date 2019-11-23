/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edge_to_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:10:42 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 17:12:17 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				add_edge_to_node(t_node *node, t_str *neighbor, long wght)
{
	t_edge			*edge;

	edge = create_edge(node->name, neighbor, wght);
	if (edge == NULL)
		return (FALSE);
	if (ft_dictset(node->edge, neighbor->con, edge) == FALSE)
	{
		del_edge(&edge);
		return (FALSE);
	}
	return (TRUE);
}
