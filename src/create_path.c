/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 00:10:35 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 01:11:40 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path				*create_path(void)
{
	t_path			*path;

	path = (t_path*)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);
	path->rooms = ft_vnew(INITIAL_FLOWS * sizeof(void*), sizeof(void*));
	if (path->rooms == NULL)
	{
		ft_memdel((void**)&path);
		return (NULL);
	}
	path->ants = -1;
	path->len_path = 0;
	path->printable = FALSE;
	return (path);
}
