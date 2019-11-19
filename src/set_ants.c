/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:13 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/19 22:27:07 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				set_ants(t_farm *farm)
{
	char		*line;
	long		ants;

	line = ft_vnext_con(farm->buffer);
	if (ft_isnumeric_str(line) == FALSE)
		return (FALSE);
	ants = ft_atol(line);
	if (ants < 0)
		return (FALSE);
	farm->ants = (ants > INT_MAX ? INT_MAX : (int)ants);
	return (TRUE);
}
