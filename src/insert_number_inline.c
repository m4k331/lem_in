/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_number_inline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:42:30 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 21:49:32 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					insert_number_inline(char *line, long num)
{
	const int		len = ft_numlen(num, 10);
	int				iter;

	iter = len;
	while (iter--)
	{
		line[iter] = (char)((num % 10) + '0');
		num /= 10;
	}
	return (len);
}
