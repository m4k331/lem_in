/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:04:21 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 01:52:51 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					destroy_flow(void *flow)
{
	ft_vmap(((t_flow*)flow)->paths, 0, destroy_path);
	ft_vdel(&((t_flow*)flow)->paths);
	ft_memdel((void**)&flow);
	return (TRUE);
}
