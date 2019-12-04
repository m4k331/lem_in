/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:43:59 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 21:43:59 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_steps(t_flows *flows, int fd, int8_t color)
{
	char			result[PREFIX_LN + MAX_NUMBER_LN + SUFFIX_END_LN];
	int				len;

	if (color == TRUE)
	{
		ft_memcpy(result, GOLD, PREFIX_LN);
		len = insert_number_inline(result + PREFIX_LN, flows->best_steps);
		ft_memcpy(result + PREFIX_LN + len, SUFFIX_END, SUFFIX_END_LN);
		write(fd, result, PREFIX_LN + len + SUFFIX_END_LN);
	}
	else
	{
		len = insert_number_inline(result, flows->best_steps);
		result[len] = NL;
		write(fd, result, len + 1);
	}
}
