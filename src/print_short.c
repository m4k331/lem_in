/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:45:39 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/09 14:10:10 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t		preparing_print(t_display *d, char **line)
{
	t_path			**path;
	long			len;
	long			count;

	len = 0;
	count = 0;
	d->flows->max_flow->paths->iter = -1;
	path = ft_vnext_con(d->flows->max_flow->paths);
	while (path)
	{
		len += (*path)->len_path;
		count += (*path)->rooms->head;
		if (convert_path_to_printable(*path) == FALSE)
			return (FALSE);
		path = ft_vnext_con(d->flows->max_flow->paths);
	}
	if (d->farm->direct)
		len = DIRECT_BUFF_SZ;
	else
		len += count * (24 + (d->colors ? COLOR_LN : 0)) + DISCOLOR_END_LN;
	*line = (char*)malloc(len * sizeof(char));
	return ((*line == NULL ? FALSE : TRUE));
}

int8_t				print_short(t_display *d)
{
	char			*line;

	indent_control(d);
	if (preparing_print(d, &line) == FALSE)
		return (FALSE);
	if (d->farm->direct == TRUE)
		print_direct_path(d, line);
	else
		print_complex_path(d, line);
	ft_memdel((void**)&line);
	return (TRUE);
}
