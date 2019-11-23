/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hash_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:21:00 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 16:30:57 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define INSERT_HASH(str) (*(str) = '#')

static inline t_str		*get_hash_name(t_str *name)
{
	t_str				*hash_name;
	char				*hash_con;

	hash_con = (char*)malloc(name->len + 2);
	if (hash_con == NULL)
		return (NULL);
	INSERT_HASH(hash_con);
	ft_memcpy(hash_con + 1, name->con, name->len + 1);
	hash_name = ft_tstrbuilt(hash_con, name->len + 1);
	if (hash_name == NULL)
	{
		ft_memdel((void**)&hash_con);
		return (NULL);
	}
	return (hash_name);
}

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
