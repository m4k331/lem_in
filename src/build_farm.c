/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:28:02 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/24 22:28:55 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_farm	*init_farm(void)
{
	t_farm				*farm;

	farm = (t_farm*)ft_memalloc(sizeof(t_farm));
	if (farm == NULL)
		return (NULL);
	farm->nodes = ft_dictnew(LEMIN_INIT_DICT_SIZE);
	if (farm->nodes == NULL)
	{
		ft_memdel((void**)&farm);
		return (NULL);
	}
	return (farm);
}

int						prnt(void *e)
{
	t_node				*node;

	node = *(t_node**)e;
	print_node(node);
}

t_farm					*build_farm(t_vector *buffer)
{
	t_farm				*farm;

	farm = init_farm();
	if (farm == NULL)
		return (NULL);
	if (fill_farm(farm, buffer) == FALSE)
	{
		destroy_farm(&farm);
		return (NULL);
	}
	ft_dictiterate(farm->nodes, prnt);
	return (farm);
}
