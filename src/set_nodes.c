/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/24 01:22:48 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** set_nodes - parses the buffer and creates nodes in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/
int8_t					set_nodes(t_farm *farm, t_vector *buffer)
{
	t_str				*str;
	int8_t				state;
	uint8_t				specifier;

	specifier = MASK_COMMON;
	while (TRUE)
	{
		str = *(t_str**)ft_vnext_con(buffer);
		if (str == NULL)
			return (ERROR);
		if (IS_COMMON(specifier) && STARTS_WITH_HASH(str->con))
		{
			if (ft_strcmp(CMD_START, str->con) == 0)
				specifier = MASK_START;
			else if (ft_strcmp(CMD_END, str->con) == 0)
				specifier = MASK_END;
		}
		else
		{
			state = add_node(farm, str, specifier);
			specifier = MASK_COMMON;
			if (state != SUCCESS)
				return (state);
		}
	}
}
