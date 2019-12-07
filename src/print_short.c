/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:45:39 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 21:59:12 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t		preparing_printing(t_flow *flow, \
										t_vector *colors, \
										char **line, \
										long *ants)
{
	t_path			**path;
	long			len;
	long			count;

	*ants = 0;
	len = 0;
	count = 0;
	flow->paths->iter = -1;
	path = ft_vnext_con(flow->paths);
	while (path)
	{
		*ants += (*path)->ants;
		if (len < (*path)->len_path)
			len = (*path)->len_path;
		if (count < (*path)->rooms->head)
			count = (*path)->rooms->head;
		if (convert_path_to_printable(*path) == FALSE)
			return (FALSE);
		path = ft_vnext_con(flow->paths);
	}
	len += count * (NUM_MAX_LN + 3 + (colors ? COLOR_LN : 0)) + DISCOLOR_END_LN;
	*line = (char*)malloc(len * sizeof(char));
	return ((*line == NULL ? FALSE : TRUE));
}

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

int8_t				print_short(int fd, t_vector *colors, t_flows *flows)
{
	char			*line;
	long			ants;
	long			num_ant;
	long			finished_ants;

	if (preparing_printing(flows->max_flow, colors, &line, &ants) == FALSE)
		return (FALSE);
	num_ant = 1;
	finished_ants = 0;
	while (finished_ants != ants)
	{
		push_ants_one_wave(flows->max_flow, colors, &num_ant, &finished_ants);
		print_position_ants(fd, line, flows->max_flow, colors);
	}
	ft_memdel((void**)&line);
	return (TRUE);
}
