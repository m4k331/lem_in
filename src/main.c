/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 18:01:25 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						main(int ac, char **av)
{
	uint8_t				opts;

	process_supplied_options(&opts, ac, av);
	if (IS_USAGE(opts))
		show_usage(*av);
	if (IS_MULTI(opts))
		run_multi_threads(opts, ac, av);
	else
		run(opts, NULL);
	return (0);
}
