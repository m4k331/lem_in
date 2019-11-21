/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:25:15 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/21 23:10:36 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			del(void *str)
{
	ft_tstrdel((t_str**)str);
	return (TRUE);
}

void				destroy_buffer(t_vector **buffer)
{
	if (buffer && *buffer)
	{
		(*buffer)->iter = -1;
		ft_vmap(*buffer, del);
		ft_vdel(buffer);
	}
}
