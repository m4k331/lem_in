/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_supplied_options.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:09:03 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				process_supplied_options(uint8_t *opts, int ac, char **av)
{
	*opts = 0;
	while (ac-- > 1)
	{
		av++;
		if (ft_strcmp(*av, OPT_STEPS) == 0)
			*opts |= MASK_STEPS;
		else if (ft_strcmp(*av, OPT_COLOR) == 0)
			*opts |= MASK_COLOR;
		else if (ft_strcmp(*av, OPT_PATHS) == 0)
			*opts |= MASK_PATHS;
		else if (ft_strcmp(*av, OPT_FLOWS) == 0)
			*opts |= MASK_FLOWS;
		else if (ft_strcmp(*av, OPT_SHORT) == 0)
			*opts |= MASK_SHORT;
		else if (ft_strcmp(*av, OPT_MULTI) == 0)
			*opts |= MASK_MULTI;
		else if ((*opts & MASK_MULTI) == FALSE)
			*opts |= MASK_USAGE;
	}
}
