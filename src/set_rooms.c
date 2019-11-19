/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/20 01:46:36 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	is_room(char *line)
{
	char			*name;
	char			*x;
	char			*y;

	printf("_%s_\n", line);
	y = ft_strrchr(line, ' ');
	if (y == NULL)
		return (FALSE);
	*y++ = '\0';
	x = ft_strrchr(line, ' ');
	if (x == NULL)
		return (FALSE);
	*x++ = '\0';
	name = line;
	if (name == NULL)
		return (FALSE);
	printf("name:{%s} x:{%s} y:{%s}\n", name, x, y);
	return (TRUE);
}

int					set_rooms(t_farm *farm)
{
	char			*line;

	while (TRUE)
	{
		line = ft_vnext_con(farm->buffer);
		if (is_room(line))
			printf("%s - room\n", line);
		else
			break ;
	}
	return (TRUE);
}
