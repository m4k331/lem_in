/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:40:29 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 01:52:51 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					destroy_path(void *p)
{
	t_path			**path;

	path = p;
	if ((*path)->printable == TRUE)
		ft_vmap((*path)->rooms, 0, destroy_room);
	ft_vdel(&(*path)->rooms);
	ft_memdel(p);
	return (TRUE);
}
