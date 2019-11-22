/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 04:44:45 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					main(int ac, char **av)
{
	t_farm			farm;

	read_stdin(&farm.buffer);
	if (set_ants(&farm) == FALSE)
	{
		perror("ERROR parsing ants");
		/// to do destroy farm
		exit(1);
	}
//	print_buffer(farm.buffer);
	printf("ants:%d\n", farm.ants);
//	destroy_buffer(&farm.buffer);
	set_rooms(&farm);
	return (0);
}
