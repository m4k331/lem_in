/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 00:59:39 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 18:57:37 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			prnt(void *e)
{
	char			*t;
	int64_t			w;
	int8_t			fl;
	t_edge			*edge;

	edge = (t_edge*)e;
	t = edge->neighbor ? edge->neighbor->name->con : NULL;
	w = edge->weight;
	fl = edge->flow;
	printf(" (%s, %ld, %d) ", t, w, fl);
	return (TRUE);
}

void				print_node(t_node *node)
{
	char			*n = node->name->con;
	char			*p = (node->predecessor ? node->predecessor->name->con : NULL);
	long			d = node->delta;
	long			pot = node->potential;
	uint8_t			m = node->marks;

	printf("%s<-%s d:%ld p:%ld m:%d [", n, p, d, pot, m);
	if (node->edge)
		ft_dictiterate(node->edge, prnt);
	printf("]\n");
}
