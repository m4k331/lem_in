/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:28:02 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 22:01:16 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_farm	*init_farm(void)
{
	t_farm				*farm;

	farm = (t_farm*)ft_memalloc(sizeof(t_farm));
	if (farm == NULL)
		return (NULL);
	farm->rooms = ft_dictnew(LEMIN_INIT_DICT_SIZE);
	if (farm->rooms == NULL)
	{
		ft_memdel((void**)&farm);
		return (NULL);
	}
	return (farm);
}

t_farm					*build_farm(t_vector *buffer)
{

}
