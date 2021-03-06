/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hash_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:21:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/24 19:41:42 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node					*create_hash_node(t_str *name)
{
	t_node				*node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->name = get_hash_name(name);
	if (node->name == NULL)
	{
		ft_memdel((void**)&node);
		return (NULL);
	}
	node->edge = ft_dictnew(0);
	if (node->edge == NULL)
	{
		ft_tstrdel(&node->name);
		ft_memdel((void**)&node);
		return (NULL);
	}
	node->delta = INF;
	return (node);
}
