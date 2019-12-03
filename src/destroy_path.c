/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:40:29 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 01:46:27 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					destroy_path(void *path)
{
	if (((t_path*)path)->printable == TRUE)
		ft_vmap(((t_path*)path)->rooms, 0, destroy_room);
	ft_vdel(&((t_path*)path)->rooms);
	ft_memdel((void**)&path);
	return (TRUE);
}
