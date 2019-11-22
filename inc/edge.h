/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:56:18 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 20:00:34 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDGE_H
# define EDGE_H

typedef struct		s_edge
{
	t_str			*from;
	t_str			*to;
	int64_t			weight;
	int8_t			flow;
}					t_edge;

t_edge				*create_edge(t_str *from, t_str *to, int64_t weight);
void				del_edge(t_edge **edge);

#endif
