/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_direct_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:54:33 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
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

static inline void	insert_step_inline(t_display *d, char **line, long num)
{
	if (d->colors)
		insert_color_inline(d->colors, line);
	ft_memcpy(*line, " L", 2);
	(*line) += 2;
	(*line) += insert_number_inline(*line, num);
	ft_memcpy(*line, "-", 1);
	(*line)++;
	ft_memcpy(*line, d->farm->end->name->con, d->farm->end->name->len);
	(*line) += d->farm->end->name->len;
}

static inline void	update_buffer(t_display *d, char **shift, char **line)
{
	size_t			len;

	len = (*shift) - (*line);
	if (len + 1024 >= DIRECT_BUFF_SZ)
	{
		write(d->fd, (*line), len);
		*shift = *line;
	}
}

void				print_direct_path(t_display *d, char *line)
{
	long			num;
	char			*shift;

	shift = line;
	insert_first_step_inline(d, &shift);
	num = 2;
	while (num <= d->farm->ants)
	{
		insert_step_inline(d, &shift, num++);
		update_buffer(d, &shift, &line);
	}
	if (d->colors)
	{
		ft_memcpy(shift, DISCOLOR, DISCOLOR_LN);
		shift += DISCOLOR_LN;
	}
	ft_memcpy(shift++, "\n", 1);
	write(d->fd, line, shift - line);
}
