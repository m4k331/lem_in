/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 23:20:24 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 23:22:27 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node				*create_node(t_str *name)
{
	t_node			*node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->name = ft_tstrdup(name);
	if (node->name == NULL)
	{
		ft_memdel((void**)&node);
		return (NULL);
	}
	return (node);
}
