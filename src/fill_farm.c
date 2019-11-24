/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:13:40 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/25 01:02:58 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	check_valid_buffer_end(t_vector *buffer)
{
	return (ft_vnext_con(buffer) == NULL && buffer->iter == buffer->head);
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
	if (check_valid_buffer_end(buffer) == FALSE)
	{
		perror("ERROR input data");
		return (FALSE);
	}
	return (TRUE);
}
