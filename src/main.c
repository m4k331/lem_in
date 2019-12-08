/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 00:26:29 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	buffer_filling(t_vector **buffer, char *file)
{
	int				fd;

	fd = (file == NULL ? STDIN_FILENO : open(file, O_RDONLY));
	(*buffer) = get_fd_buffer(fd);
	if ((*buffer) == NULL)
	{
		perror("ERROR reading buffer");
		return (FALSE);
	}
	if (fd != STDIN_FILENO && close(fd) == -1)
	{
		perror("ERROR closing fd");
		destroy_buffer(buffer);
		return (FALSE);
	}
	return (TRUE);
}

static inline int	processing_buffer_to_farm(t_vector **buffer, \
											t_farm **farm, \
											char *file)
{
	(*farm) = build_farm(*buffer, file);
	if ((*farm) == NULL)
	{
		destroy_buffer(buffer);
		return (FALSE);
	}
	return (TRUE);
}

static inline int	calculate_flow_of_ants_in_farm(t_vector **buffer, \
													t_farm **farm, \
													t_flows **flows)
{
	(*flows) = search_flows(*farm);
	if ((*flows) == NULL)
	{
		destroy_buffer(buffer);
		destroy_farm(farm);
		return (FALSE);
	}
	return (TRUE);
}

static inline void	run(uint8_t opts, char *file)
{
	t_vector		*buffer;
	t_farm			*farm;
	t_flows			*flows;

	if (buffer_filling(&buffer, file) == FALSE)
		return ;
	if (processing_buffer_to_farm(&buffer, &farm, file) == FALSE)
		return ;
	if (calculate_flow_of_ants_in_farm(&buffer, &farm, &flows) == FALSE)
		return ;
	display_solution(opts, buffer, farm, flows);
	destroy_buffer(&buffer);
	destroy_farm(&farm);
	destroy_flows(&flows);
}

int					main(int ac, char **av)
{
	int				count;
	int				iter;
	uint8_t			opts;

	process_supplied_options(&opts, ac, av);
	if (IS_USAGE(opts))
		show_usage(*av);
	if (IS_MULTI(opts))
	{
		count = get_count_files(ac, av);
		if (count == 0)
			show_usage(*av);
		iter = 0;
		while (iter < count)
		{
			run(opts, av[ac - count + iter]);
			iter++;
		}
	}
	else
		run(opts, NULL);
	return (0);
}
