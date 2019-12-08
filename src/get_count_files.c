/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_count_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:26:34 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 00:26:55 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t				get_count_files(int ac, char **av)
{
	int				iter;
	int				count;

	iter = 1;
	count = 0;
	while (iter < ac && IS_OPTION(av[iter]))
		iter++;
	while (iter < ac)
	{
		if (IS_OPTION(av[iter]))
			return (0);
		else
			count++;
		iter++;
	}
	return (count);
}
