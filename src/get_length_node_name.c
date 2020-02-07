/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length_node_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 01:37:10 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns the number of characters of the node name in the raw string
*/

size_t					get_length_node_name(t_str *raw_str)
{
	size_t				len;
	char				*first;
	char				*second;

	len = raw_str->len;
	first = ft_memrchr(raw_str->con, SPACE, len);
	if (first == NULL || ft_isnumeric_str(first + 1, FALSE) == FALSE)
		return (0);
	len = (size_t)first - (size_t)raw_str->con - 1;
	second = ft_memrchr(raw_str->con, SPACE, len);
	*first = NULL_TERMINATE;
	if (second == NULL || ft_isnumeric_str(second + 1, FALSE) == FALSE)
	{
		*first = SPACE;
		return (0);
	}
	*first = SPACE;
	len = (size_t)second - (size_t)raw_str->con;
	if ((*raw_str->con == '#' || *raw_str->con == 'L') || \
											ft_memchr(raw_str->con, SEP, len))
		return (0);
	return (len);
}
