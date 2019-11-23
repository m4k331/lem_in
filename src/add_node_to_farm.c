/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_to_farm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:49:29 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 04:49:29 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t					add_node_to_farm(t_farm *farm, t_node *node)
{
	if (ft_dictget(farm->nodes, node->name->con) != NULL)
		return (FALSE);
	if (ft_dictset(farm->nodes, node->name->con, node) == FALSE)
		return (FALSE);
	return (TRUE);
}
