/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:36:23 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/18 22:14:36 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_buffer(t_vector *buffer)
{
	char			*line;
	size_t			len;

	buffer->iter = -1;
	while (buffer->iter < buffer->head)
	{
		line = (char*)ft_vnext_con(buffer);
		len = ft_strlen(line);
		line[len] = '\n';
		write(1, line, len + 1);
		line[len] = '\0';
	}
}
