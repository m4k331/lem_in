/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 00:57:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/05 17:21:23 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t					print_paths(int fd, t_vector *colors, t_flows *flows)
{
	t_path				**path;
	long				shift;

	flows->max_flow->paths->iter = -1;
	path = ft_vnext_con(flows->max_flow->paths);
	if (colors)
	{
		shift = PATH_SHIFT_COLOR;
		while (path)
		{
			if (display_color_path(fd, ft_vat(colors, shift++), *path) == FALSE)
				return (FALSE);
			path = ft_vnext_con(flows->max_flow->paths);
		}
	}
	else
	{
		while (path)
		{
			if (display_path(fd, *path) == FALSE)
				return (FALSE);
			path = ft_vnext_con(flows->max_flow->paths);
		}
	}
	return (TRUE);
}
