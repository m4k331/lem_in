/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_supplied_options.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:09:03 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 17:56:51 by ahugh            ###   ########.fr       */
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
			TO_STEPS(*opts);
		else if (ft_strcmp(*av, OPT_COLOR) == 0)
			TO_COLOR(*opts);
		else if (ft_strcmp(*av, OPT_PATHS) == 0)
			TO_PATHS(*opts);
		else if (ft_strcmp(*av, OPT_FLOWS) == 0)
			TO_FLOWS(*opts);
		else if (ft_strcmp(*av, OPT_SHORT) == 0)
			TO_SHORT(*opts);
		else if (ft_strcmp(*av, OPT_MULTI) == 0)
			TO_MULTI(*opts);
		else if (!IS_MULTI(*opts))
			TO_USAGE(*opts);
	}
}
