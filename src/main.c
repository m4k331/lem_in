/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/01 22:48:25 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						prnt(void *node)
{
	print_node(node);
	return (TRUE);
}

int					main(int ac, char **av)
{
	t_farm			*farm;
	t_vector		*buffer;
	const int		fd = open("/home/ahugh/lem_in/mp", O_RDONLY);

	buffer = get_fd_buffer(fd);
	if (buffer == NULL)
	{
		perror("ERROR reading fd");
		return (1);
	}
	if (close(fd) == -1)
	{
		destroy_buffer(&buffer);
		perror("ERROR closing fd");
		return (1);
	}
	farm = build_farm(buffer);
	if (farm == NULL)
	{
		destroy_buffer(&buffer);
		return (1);
	}
	dijkstra(farm);
	print_buffer(buffer);
	ft_dictiterate(farm->nodes, prnt);
	destroy_buffer(&buffer);
	destroy_farm(&farm);
	return (0);
}
