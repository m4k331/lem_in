/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_farm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 22:25:16 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 22:28:27 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			del(void *node)
{
	///to do del_node
}

void				destroy_farm(t_farm **farm)
{
	if ((*farm)->rooms)
		ft_dictdel(&(*farm)->rooms, del);
	ft_memdel((void**)farm);
}
