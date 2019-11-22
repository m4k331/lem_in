/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 19:01:59 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static inline int	get_space_idx(t_str *str, int last_idx)
{
	char			*space;

	space = ft_memrchr(str->con, SPACE, last_idx);
	if (space == NULL)
		return (-1);
	*space++ = NULL_TERMINATE;
	return ((int)((size_t)space - (size_t)str->con));
}


static inline int	add_room(t_farm *farm, t_str *str, uint8_t specifier)
{
	char			*x;
	char			*y;
	size_t			len;

	int ix = get_space_idx(str, str->len);
	printf("idx[%d]->|%s|\n", ix, &str->con[ix]);
	int iy = get_space_idx(str, ix);
	printf("idx[%d]->|%s|\n", iy, &str->con[iy]);
	if (iy > 1)
		printf("name->|%s|\n", str->con);
	else
		printf("Not name\n");
	str->con[ix - 1] = SPACE;
	str->con[iy - 1] = SPACE;
	printf("%s\n\n", str->con);
	return (TRUE);
}

/*
** set_rooms - parses the buffer and creates rooms in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/
int8_t				set_rooms(t_farm *farm)
{
	t_str			*str;
	int8_t			state;
	uint8_t			specifier;

	specifier = MASK_COMMON;
	while (TRUE)
	{
		str = *(t_str**)ft_vnext_con(farm->buffer);
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
			state = add_room(farm, str, specifier);
			specifier = MASK_COMMON;
			if (state != SUCCESS)
				return (state);
		}
	}
}
