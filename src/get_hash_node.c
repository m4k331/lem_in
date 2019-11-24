/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:49:33 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/24 21:21:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** gets the hash node from the farm, otherwise NULL
*/
t_node				*get_hash_node(t_farm *farm, t_str *name)
{
	t_node			*hash_node;
	t_str			*hash_name;

	hash_name = get_hash_name(name);
	if (hash_name == NULL)
		return (NULL);
	hash_node = ft_dictget(farm->nodes, hash_name->con);
	ft_tstrdel(&hash_name);
	return (hash_node);
}
