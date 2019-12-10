/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:40:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** converts a name to a hash name, otherwise return NULL
*/

t_str				*get_hash_name(t_str *name)
{
	t_str			*hash_name;
	char			*hash_con;

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
