/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_farm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 22:25:16 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 20:27:06 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				destroy_farm(t_farm **farm)
{
	if ((*farm)->nodes)
		ft_dictdel(&((*farm)->nodes), destroy_node);
	ft_memdel((void**)farm);
}
