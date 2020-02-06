/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/18 00:01:52 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void		handle_commands(t_str *raw_str, uint8_t *type)
{
	if (ft_strcmp(CMD_START, raw_str->con) == 0)
		*type = MASK_START;
	else if (ft_strcmp(CMD_END, raw_str->con) == 0)
		*type = MASK_END;
}

/*
** set_nodes - parses the buffer and creates nodes in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/

int8_t					set_nodes(t_farm *farm, t_vector *buffer)
{
	t_str				**raw_str;
	int8_t				state;
	uint8_t				type;

	type = MASK_COMMON;
	while (TRUE)
	{
		raw_str = ft_vnext_con(buffer);
		if (raw_str == NULL)
			return (ERROR);
		if (*((*raw_str)->con) == '#')
			handle_commands(*raw_str, &type);
		else
		{
			state = add_node_to_farm(farm, *raw_str, type);
			if (state != SUCCESS)
				return ((type & MASK_COMMON ? state : ERROR));
			type = MASK_COMMON;
		}
	}
}
