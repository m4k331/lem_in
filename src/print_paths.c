/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 00:57:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int8_t	print_color(t_display *d, t_path **path)
{
	long				s;

	s = PATH_SHIFT_COLOR;
	while (path)
	{
		if (display_color_path(d->fd, ft_vat(d->colors, s++), *path) == FALSE)
			return (FALSE);
		path = ft_vnext_con(d->flows->max_flow->paths);
	}
	return (TRUE);
}

static inline int8_t	print_discolor(t_display *d, t_path **path)
{
	while (path)
	{
		if (display_path(d->fd, *path) == FALSE)
			return (FALSE);
		path = ft_vnext_con(d->flows->max_flow->paths);
	}
	return (TRUE);
}

int8_t					print_paths(t_display *d)
{
	t_path				**path;

	indent_control(d);
	d->flows->max_flow->paths->iter = -1;
	path = ft_vnext_con(d->flows->max_flow->paths);
	if (d->colors)
	{
		if (print_color(d, path) == FALSE)
			return (FALSE);
	}
	else
	{
		if (print_discolor(d, path) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
