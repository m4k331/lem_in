/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:43:59 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 23:59:01 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_steps(t_flows *flows, int fd, t_vector *colors)
{
	char			result[COLOR_LN + NUM_MAX_LN + DISCOLOR_END_LN];
	int				len;

	if (colors)
	{
		ft_memcpy(result, ft_vat(colors, 220), COLOR_LN);
		len = insert_number_inline(result + COLOR_LN, flows->best_steps);
		ft_memcpy(result + COLOR_LN + len, DISCOLOR_END, DISCOLOR_END_LN);
		write(fd, result, COLOR_LN + len + DISCOLOR_END_LN);
	}
	else
	{
		len = insert_number_inline(result, flows->best_steps);
		result[len] = NL;
		write(fd, result, len + 1);
	}
}