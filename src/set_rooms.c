/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 02:21:54 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns the number of characters in the room name
*/
static inline size_t	get_length_room_name(t_str *str)
{
	size_t				len;
	char				*con;

	len = str->len;
	con = ft_memrchr(str->con, SPACE, len);
	if (con == NULL || ft_isnumeric_str(con + 1, FALSE) == FALSE)
		return (0);
	len =(size_t)con - (size_t)str->con;
	con = ft_memrchr(str->con, SPACE, len);
	if (con == NULL || ft_isnumeric_str(con + 1, FALSE) == FALSE)
		return (0);
	len = (size_t)con - (size_t)str->con;
	if (IS_FORBIDDEN_SYMBOLS(*str->con) || ft_memchr(str->con, SEP, len))
		return (0);
	return (len);
}

//static inline t_node	*get_node(t_str *str)
//{
//	t_node				*node;
//	int					len;
//	char				*y;
//	char				*x;
//
//	len = str->len;
//	y = get_split_content(str);
//	if (y == NULL || ft_isnumeric_str(y, FALSE) == FALSE)
//		return (NULL);
//	str->len =(int)((size_t)y - (size_t)str->con) - 1;
//	x = get_split_content(str);
//	if (x == NULL || ft_isnumeric_str(x, FALSE) == FALSE)
//		return (NULL);
//	str->len = (int)((size_t)x - (size_t)str->con) - 1;
//	if (str->len < 1 || str->con[0] == '#' || str->con[0] == 'L' || \
//											ft_memchr(str->con, '-', str->len))
//		return (NULL);
//	node = create_node(str);
//	*(y - 1) = SPACE;
//	*(x - 1) = SPACE;
//	str->len = len;
//	return ((node == NULL ? ERROR_CREATE_NODE : node));
//}

static inline int8_t	add_room(t_farm *farm, t_str *str, uint8_t specifier)
{
	t_node				*node;

	node = get_node(str);
	if (node == ERROR_CREATE_NODE)
		return (ERROR);
	if (node)
	{
		printf("%s - %zu\n%s - %zu\n\n", str->con, str->len, node->name->con, node->name->len);
		return (SUCCESS);
	}
	else
		return (FAIL);
}

/*
** set_rooms - parses the buffer and creates rooms in the farm
** returns: 0 in case of parsing completion and -1 in case of error
*/
int8_t					set_rooms(t_farm *farm, t_vector *buffer)
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
			state = add_room(farm, str, specifier);
			specifier = MASK_COMMON;
			if (state != SUCCESS)
				return (state);
		}
	}
}
