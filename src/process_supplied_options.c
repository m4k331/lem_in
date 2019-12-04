/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_supplied_options.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:09:03 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 17:10:06 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	apply_option(uint8_t *options, char *opt)
{
	if (ft_strcmp(opt, OPT_STEPS) == 0)
		*options |= 1u;
	else if (ft_strcmp(opt, OPT_COLOR) == 0)
		*options |= 2u;
	else if (ft_strcmp(opt, OPT_PATHS) == 0)
		*options |= 4u;
	else if (ft_strcmp(opt, OPT_FLOWS) == 0)
		*options |= 8u;
	else if (ft_strcmp(opt, OPT_FLOWS) == 0)
		*options |= 16u;
	else if (ft_strcmp(opt, OPT_SHORT) == 0)
		*options |= 32u;
	else if (ft_strcmp(opt, OPT_MULTI) == 0)
		*options |= 64u;
	else
		*options = 128u;
}

void				process_supplied_options(uint8_t *opts, int ac, char **av)
{
	int				iter;

	*opts = 0;
	if (ac > 1)
	{
		iter = 0;
		while (iter < ac)
		{
			apply_option(opts, av[iter]);
			iter++;
		}
	}
}
