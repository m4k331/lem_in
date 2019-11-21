/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:36:23 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/21 23:21:01 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			print(void *str)
{
	ft_tstrputendl(*(t_str**)str);
	return (TRUE);
}

void				print_buffer(t_vector *buffer)
{
	buffer->iter = -1;
	ft_vmap(buffer, print);
}
