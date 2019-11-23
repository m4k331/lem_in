/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:23:09 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 20:47:09 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				destroy_node(void *n)
{
	t_node			*node;

	node = *(t_node**)n;
	ft_tstrdel(&node->name);
	if (node->edge)
		ft_dictdel(&node->edge, del_edge);
	ft_memdel((void**)n);
}
