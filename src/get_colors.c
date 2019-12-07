/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 23:47:04 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/07 21:59:12 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void		insert_fixed_len_number(char *line, long num, int len)
{
	while (len--)
	{
		line[len] = (char)((num % 10) + '0');
		num /= 10;
	}
}

t_vector				*get_colors(int count_color)
{
	t_vector			*colors;
	char				*con;

	colors = ft_vnew((COLOR_LN) * (count_color + 1), COLOR_LN);
	if (colors == NULL)
		return (NULL);
	con = colors->con;
	while (colors->head < count_color)
	{
		ft_memcpy(con, COLOR_CODE, COLOR_PREFIX_LN);
		con += COLOR_PREFIX_LN;
		insert_fixed_len_number(con, colors->head, FIXED_NUM_LN);
		con += FIXED_NUM_LN;
		*con = COLOR_CODE[10];
		con++;
		colors->head++;
	}
	return (colors);
}
