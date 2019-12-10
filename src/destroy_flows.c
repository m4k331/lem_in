/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_flows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:50:09 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/02 23:04:19 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				destroy_flows(t_flows **flows)
{
	ft_vmap((*flows)->flows, 0, destroy_flow);
	ft_vdel(&((*flows)->flows));
	ft_memdel((void**)flows);
}
