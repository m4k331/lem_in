/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:18:43 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/05 00:02:28 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	indent_control(int8_t *indent)
{
	if (*indent == TRUE)
		ft_putchar(NL);
	*indent = TRUE;
}

void				display_solution(uint8_t opts, \
									t_vector *buffer, \
									t_farm *farm, \
									t_flows *flows)
{
	t_vector		*colors;
	int8_t			indent;
	int				fd;

	fd = 1;
	indent = FALSE;
	colors = IS_COLOR(opts) && IS_MULTI(opts) == FALSE ? get_colors(MC) : NULL;
	if (IS_STEPS(opts))
	{
		indent_control(&indent);
		print_steps(flows, fd, colors);
	}
	if (IS_PATHS(opts))
	{
		indent_control(&indent);
	}
	ft_vdel(&colors);
	exit(fd);
}
