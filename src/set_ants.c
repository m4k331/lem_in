/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:13 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/24 17:04:15 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** set_ants - gets the number of ants from the buffer and sets it in the farm
** in case of success, returns 1, otherwise 0
*/
int8_t				set_ants(t_farm *farm, t_vector *buffer)
{
	t_str			*raw_str;
	long			ants;

	raw_str = *(t_str**)ft_vnext_con(buffer);
	if (ft_isnumeric_str(raw_str->con, FALSE) == FALSE)
		return (FALSE);
	ants = ft_atol(raw_str->con);
	if (ants < 0)
		return (FALSE);
	farm->ants = (ants > INT_MAX ? INT_MAX : (int)ants);
	return (TRUE);
}
