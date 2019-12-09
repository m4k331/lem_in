/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multi_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:59:34 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 18:56:02 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					*thread_run(void *data)
{
	run(((t_data*)data)->opts, ((t_data*)data)->file);
	pthread_exit(0);
}

static t_data			*create_data(uint8_t opts, int count, char **av)
{
	t_data				*data;
	int					iter;

	data = (t_data*)malloc(sizeof(t_data) * count);
	if (data == NULL)
		return (data);
	iter = 0;
	while (iter < count)
	{
		data[iter].opts = opts;
		data[iter].file = av[iter];
		iter++;
	}
	return (data);
}

static inline void		thread_preparation(pthread_t **threads, int count)
{
	*threads = (pthread_t*)malloc(sizeof(pthread_t) * count);
	if (*threads == NULL)
	{
		perror("ERROR creating threads");
		exit(1);
	}
}

static inline t_data	*get_data(pthread_t **threads, \
								char **av,
								int count,
								uint8_t opts)
{
	t_data				*data;

	data = create_data(opts, count, av);
	if (data == NULL)
	{
		ft_memdel((void**)&threads);
		perror("ERROR creating data");
		exit(1);
	}
	return (data);
}

void					run_multi_threads(uint8_t opts, int ac, char **av)
{
	pthread_t			*threads;
	t_data				*data;
	int					count;
	int					iter;

	count = get_count_files(ac, av);
	if (count == 0)
		show_usage(*av);
	thread_preparation(&threads, count);
	data = get_data(&threads, av + ac - count, count, opts);
	iter = 0;
	while (iter < count)
	{
		pthread_create(&threads[iter], NULL, thread_run, &data[iter]);
		iter++;
	}
	iter = 0;
	while (iter < count)
	{
		pthread_join(threads[iter], NULL);
		iter++;
	}
}
