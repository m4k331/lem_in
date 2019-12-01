/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:01:54 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/01 19:55:51 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						prnt(void *node)
{
	print_node(node);
	return (TRUE);
}

int					cmp_heap(void *a, void *b)
{
	return ((*(t_node**)a)->delta > (*(t_node**)b)->delta);
}

int8_t				initial_heap(t_fib **heap, t_farm *farm)
{
	t_node			*node;

	*heap = ft_fibnew(cmp_heap, NULL);
	if (*heap == NULL)
		return (FALSE);
	farm->nodes->items->iter = -1;
	node = ft_dictnext_item(farm->nodes);
	while (node)
	{
		ft_fibpush(*heap, node);
		node = ft_dictnext_item(farm->nodes);
	}
	return (TRUE);
}

int8_t				dijkstra(t_farm *farm)
{
	t_fib			*heap;

	initial_heap(&heap, farm);
	if (heap == NULL)
		return (FALSE);
	printf("%s\n", ((t_node*)ft_fibpop(heap))->name->con);
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
