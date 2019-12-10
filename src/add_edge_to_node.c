/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edge_to_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:10:42 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 17:14:07 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				add_edge_to_node(t_node *from, t_node *to, int8_t weight)
{
	t_edge			*edge;

	if (ft_dictget(from->edge, to->name->con) != NULL)
		return (TRUE);
	edge = create_edge(to, weight);
	if (edge == NULL)
		return (FALSE);
	if (ft_dictset(from->edge, to->name->con, edge) == FALSE)
	{
		del_edge(&edge);
		return (FALSE);
	}
	return (TRUE);
}
