/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:36:23 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_buffer(int fd, t_vector *buffer)
{
	t_str			**str;

	buffer->iter = -1;
	str = ft_vnext_con(buffer);
	while (str)
	{
		ft_tstrputendl_fd(fd, *(t_str**)str);
		str = ft_vnext_con(buffer);
	}
}
