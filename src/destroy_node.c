/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:23:09 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/23 20:34:03 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				destroy_node(void *node)
{
//	printf("del node:%s|\n",(*(t_node**)(node))->name->con);
	ft_tstrdel(&(*(t_node**)(node))->name);
	if ((*(t_node**)(node))->edge)
		ft_dictdel(&(*(t_node**)(node))->edge, del_edge);
	ft_memdel((void**)node);
}
