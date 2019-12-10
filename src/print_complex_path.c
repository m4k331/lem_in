/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_complex_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:56:19 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	insert_step(char **shift, t_vector *colors, t_room *room)
{
	if (colors)
	{
		ft_memcpy(*shift, room->color, COLOR_LN);
		(*shift) += COLOR_LN;
	}
	**shift = L;
	(*shift)++;
	(*shift) += insert_number_inline(*shift, room->ant);
	**shift = SEP;
	(*shift)++;
	ft_memcpy(*shift, room->name->con, room->name->len);
	*shift += room->name->len;
	**shift = SPACE;
	(*shift)++;
}

static inline void	insert_path_inline(t_path *path, \
										t_vector *colors, \
										char **line, \
										long *len)
{
	t_room			**room;
	char			*shift;
	int8_t			skipping;

	skipping = TRUE;
	shift = *line;
	path->rooms->iter = 0;
	room = ft_vnext_con(path->rooms);
	while (room)
	{
		if ((*room)->ant > 0)
		{
			skipping = FALSE;
			insert_step(&shift, colors, *room);
		}
		else if (skipping == FALSE)
			break ;
		room = ft_vnext_con(path->rooms);
	}
	*len += shift - *line;
	*line = shift;
}

static inline void	print_position_ants(int fd, \
										char *line, \
										t_flow *flow, \
										t_vector *colors)
{
	t_path			**path;
	long			len;

	len = 0;
	flow->paths->iter = -1;
	path = ft_vnext_con(flow->paths);
	while (path)
	{
		insert_path_inline(*path, colors, &line, &len);
		path = ft_vnext_con(flow->paths);
	}
	if (len > 0)
	{
		line--;
		if (colors)
		{
			ft_memcpy(line, DISCOLOR, DISCOLOR_LN);
			line += DISCOLOR_LN;
			len += DISCOLOR_LN;
		}
		*line = NL;
		line -= len - 1;
	}
	write(fd, line, len);
}

void				print_complex_path(t_display *d, char *line)
{
	long			num_ant;
	long			finished;

	num_ant = 1;
	finished = 0;
	while (finished != d->farm->ants)
	{
		push_ants_one_wave(d->flows->max_flow, d->colors, &num_ant, &finished);
		print_position_ants(d->fd, line, d->flows->max_flow, d->colors);
	}
}
