/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_edge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:02:51 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 17:03:42 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge				*create_edge(t_str *from, t_str *to, int64_t weight)
{
	t_edge			*edge;

	edge = (t_edge*)malloc(sizeof(t_edge));
	if (edge == NULL)
		return (NULL);
	edge->from = from;
	edge->to = to;
	edge->weight = weight;
	edge->flow = FALSE;
	return (edge);
}
