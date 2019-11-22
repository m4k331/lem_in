/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:13 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/21 22:27:53 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t			set_ants(t_farm *farm)
{
	t_str		*str;
	long		ants;

	str = *(t_str**)ft_vnext_con(farm->buffer);
	if (ft_isnumeric_str(str->con, FALSE) == FALSE)
		return (FALSE);
	ants = ft_atol(str->con);
	if (ants < 0)
		return (FALSE);
	farm->ants = (ants > INT_MAX ? INT_MAX : (int)ants);
	return (TRUE);
}
