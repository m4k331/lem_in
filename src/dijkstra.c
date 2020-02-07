/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 22:59:56 by ahugh             #+#    #+#             */
/*   Updated: 2020/02/06 21:30:07 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t		initial_heaps(t_fib **prior_heap, t_fib **conns_heap)
{
	*prior_heap = ft_fibnew(cmp_node, NULL);
	if (*prior_heap == NULL)
		return (FALSE);
	*conns_heap = ft_fibnew(cmp_node, NULL);
	if (*conns_heap == NULL)
	{
		ft_fibdel(prior_heap);
		return (FALSE);
	}
	return (TRUE);
}

static int8_t		fill_conns_heap(t_fib **conns_heap, t_node *u)
{
	t_edge			*edge;

	u->edge->items->iter = -1;
	edge = ft_dictnext_item(u->edge);
	while (edge)
	{
		if (ft_fibpush(*conns_heap, edge->neighbor) == FALSE)
			return (FALSE);
		edge = ft_dictnext_item(u->edge);
	}
	return (TRUE);
}

static inline void	relax(t_node *u, t_node *v)
{
	long			weight;
	t_edge			*edge;

	edge = ft_dictget(u->edge, v->name->con);
	weight = u->delta + edge->weight + u->potential - v->potential;
	if (weight < v->delta && edge->flow == FALSE)
	{
		v->delta = weight;
		v->predecessor = u;
	}
}

static int8_t		destroy_heaps(t_fib **prior_heap, \
									t_fib **conns_heap, \
									int8_t state)
{
	ft_fibdel(prior_heap);
	ft_fibdel(conns_heap);
	return (state);
}

int8_t				dijkstra(t_farm *farm)
{
	t_fib			*prior_heap;
	t_fib			*conns_heap;
	t_node			*u;
	t_node			*v;

	if (initial_heaps(&prior_heap, &conns_heap) == FALSE)
		return (FALSE);
	if (ft_fibpush(prior_heap, farm->start) == FALSE)
		return (destroy_heaps(&prior_heap, &conns_heap, FALSE));
	while ((prior_heap->n == 0) == FALSE)
	{
		u = ft_fibpop(prior_heap);
		u->marks |= 2;
		if (fill_conns_heap(&conns_heap, u) == FALSE)
			return (destroy_heaps(&prior_heap, &conns_heap, FALSE));
		while ((conns_heap->n == 0) == FALSE)
		{
			v = ft_fibpop(conns_heap);
			relax(u, v);
			if ((v->marks & 2) == FALSE)
				if (ft_fibpush(prior_heap, v) == FALSE)
					return (destroy_heaps(&prior_heap, &conns_heap, FALSE));
		}
	}
	return (destroy_heaps(&prior_heap, &conns_heap, TRUE));
}
