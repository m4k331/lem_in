/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 01:57:06 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 20:41:15 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		del4dict(t_room **room)
{
	free(*room);
}

void		del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}
