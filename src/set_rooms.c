/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 20:17:46 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline char		*get_split_content(t_str *str, int last_idx)
{
	char				*content;

	content = ft_memrchr(str->con, SPACE, last_idx);
	if (content == NULL)
		return (NULL);
	*content++ = NULL_TERMINATE;
	return (content);
//	return ((int)((size_t)content - (size_t)str->con));
}


static inline int8_t	add_room(t_farm *farm, t_str *str, uint8_t specifier)
{
//	char			*x;
//	char			*y;
//	size_t			len;
//
//	int ix = get_split_content(str, str->len);
//	int iy = get_split_content(str, ix);
//	str->con[ix - 1] = SPACE;
//	str->con[iy - 1] = SPACE;
//	return (TRUE);
}

/*
** set_rooms - parses the buffer and creates rooms in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/
int8_t					set_rooms(t_farm *farm)
{
	t_str				*str;
	int8_t				state;
	uint8_t				specifier;

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
