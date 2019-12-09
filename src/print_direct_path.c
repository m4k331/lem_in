/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_direct_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:54:33 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 14:35:53 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	insert_color_inline(t_vector *colors, char **line)
{
	static int		id = 1;

	ft_memcpy((*line), ft_vat(colors, id % MC), COLOR_LN);
	(*line) += COLOR_LN;
	id = id + 1;
}

static inline void	insert_first_step_inline(t_display *d, char **line)
{
	if (d->colors)
		insert_color_inline(d->colors, line);
	ft_memcpy(*line, "L", 1);
	(*line) += insert_number_inline(*line, 1);
	ft_memcpy(*line, "-", 1);
	(*line)++;
	ft_memcpy(*line, d->farm->end->name->con, d->farm->end->name->len);
	(*line) += d->farm->end->name->len;
}

void				print_direct_path(t_display *d, char *line)
{
	long			number_ant;
	char			*shift;

	shift = line;
	insert_first_step_inline(d, &shift);
	number_ant = 2;
	while (number_ant <= d->farm->ants)
	{
		if (d->colors)
			insert_color_inline(d->colors, &shift);
		ft_memcpy(shift, " L", 2);
		shift += 2;
		shift += insert_number_inline(shift, number_ant);
		ft_memcpy(shift++, "-", 1);
		ft_memcpy(shift, d->farm->end->name->con, d->farm->end->name->len);
		shift += d->farm->end->name->len;
		number_ant++;
	}
	if (d->colors)
	{
		ft_memcpy(shift, DISCOLOR, DISCOLOR_LN);
		shift += DISCOLOR_LN;
	}
	ft_memcpy(shift++, "\n", 1);
	write(d->fd, line, shift - line);
}
