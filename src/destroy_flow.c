/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:04:21 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/03 02:50:36 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					destroy_flow(void *f)
{
	t_flow			**flow;

	flow = f;
	ft_vmap((*flow)->paths, 0, destroy_path);
	ft_vdel(&((*flow)->paths));
	ft_memdel(f);
	return (TRUE);
}
