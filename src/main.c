/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 23:29:38 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int						prnt(void *node)
{
	print_node(node);
	return (TRUE);
}

//processing_the_received_options
//receiving_data
//data_processing
//solution_building
//result_output
//completion_of_work


int					main(int ac, char **av)
{
	t_farm			*farm;
	t_vector		*buffer;
	t_flows			*flows;
	const int		fd = open("/home/ahugh/py_lem_in/bigs", O_RDONLY);

	buffer = get_fd_buffer(fd);
	if (buffer == NULL)
	{
		perror("ERROR reading buffer");
		return (1);
	}
	if (fd != STDIN_FILENO && close(fd) == -1)
	{
		perror("ERROR closing fd");
		destroy_buffer(&buffer);
		return (1);
	}
	farm = build_farm(buffer);
	if (farm == NULL)
	{
		destroy_buffer(&buffer);
		return (1);
	}
	flows = search_flows(farm);
	if (flows == NULL)
	{
		destroy_farm(&farm);
		destroy_buffer(&buffer);
		return (1);
	}
	printf("BEST STEPS:%ld\n", flows->best_steps);
//	print_buffer(buffer);
//	ft_dictiterate(farm->nodes, prnt);
	destroy_buffer(&buffer);
	destroy_farm(&farm);
	destroy_flows(&flows);
	return (0);
}
