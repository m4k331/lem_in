/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:28:02 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/25 19:54:04 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initializes a new farm
*/
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

/*
** fills the farm with valid information:
** set number of ants, creates nodes and links between them
*/
int8_t					fill_farm(t_farm *farm, t_vector *buffer)
{
	if (set_ants(farm, buffer) == FALSE)
	{
		perror("ERROR setting number of ants");
		return (FALSE);
	}
	if (set_nodes(farm, buffer) == ERROR)
	{
		perror("ERROR installing node (room)");
		return (FALSE);
	}
	if (set_edges(farm, buffer) == ERROR)
	{
		perror("ERROR of installation of connections between nodes (rooms)");
		return (FALSE);
	}
	if ((ft_vnext_con(buffer) == NULL && buffer->iter == buffer->head) == FALSE)
	{
		perror("ERROR input data");
		return (FALSE);
	}
	return (TRUE);
}

static inline int8_t	farm_validation(t_farm *farm)
{
	t_vector			*stack;

	if (farm->start == NULL || farm->end == NULL)
		return (FALSE);
	farm->direct = ft_dictget(farm->start->edge, farm->end->name->con) != NULL;
	if (farm->direct == TRUE)
		return (TRUE);
	marks_reachable_nodes(farm);
	if (MARKED(farm->end->marks) == FALSE)
		return (FALSE);
	return (TRUE);
}

int						prnt(void *n)
{
	t_node				*node;

	node = *(t_node**)n;
	print_node(node);
	return (TRUE);
}

t_farm					*build_farm(t_vector *buffer)
{
	t_farm				*farm;

	farm = init_farm();
	if (farm == NULL)
	{
		perror("ERROR farm initialization");
		return (NULL);
	}
	if (fill_farm(farm, buffer) == FALSE)
	{
		destroy_farm(&farm);
		return (NULL);
	}
	if (farm_validation(farm) == FALSE)
	{
		perror("ERROR farm structure");
		destroy_farm(&farm);
		return (NULL);
	}
	ft_dictiterate(farm->nodes, prnt);
	return (farm);
}
