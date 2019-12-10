/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:43:59 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_steps(t_display *d)
{
	char			result[COLOR_LN + NUM_MAX_LN + DISCOLOR_END_LN];
	int				len;

	indent_control(d);
	if (d->colors)
	{
		ft_memcpy(result, ft_vat(d->colors, CODE_GOLD), COLOR_LN);
		len = insert_number_inline(result + COLOR_LN, d->flows->best_steps);
		ft_memcpy(result + COLOR_LN + len, DISCOLOR_END, DISCOLOR_END_LN);
		write(d->fd, result, COLOR_LN + len + DISCOLOR_END_LN);
	}
	else
	{
		len = insert_number_inline(result, d->flows->best_steps);
		result[len] = NL;
		write(d->fd, result, len + 1);
	}
}
