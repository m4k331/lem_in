/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:28:02 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** initializes a new farm
*/

static inline t_farm	*init_farm(char *file_name)
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
	farm->file = file_name;
	return (farm);
}

/*
** fills the farm with valid information:
** set number of ants, creates nodes and links between them
*/

static inline int8_t	fill_farm(t_farm *farm, t_vector *buffer)
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

/*
** function checks the reachability of the start node to the end
** 												and removes unreachable nodes
*/

static inline int8_t	farm_validation(t_farm *farm)
{
	if (farm->start == NULL || farm->end == NULL)
		return (FALSE);
	farm->direct = ft_dictget(farm->start->edge, farm->end->name->con) != NULL;
	if (farm->direct == TRUE)
		return (TRUE);
	marks_reachable_nodes(farm);
	if ((farm->end->marks & 1) == FALSE)
		return (FALSE);
	del_unmarked_nodes(farm);
	return (TRUE);
}

/*
** creates an ant farm from the buffer
** returns farm, otherwise returns NULL
*/

t_farm					*build_farm(t_vector *buffer, char *file_name)
{
	t_farm				*farm;

	farm = init_farm(file_name);
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
	return (farm);
}
