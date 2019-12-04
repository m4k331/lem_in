/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:31:22 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 18:32:40 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				show_usage(uint8_t opts, char *name_of_program)
{
	if (IS_USAGE(opts))
	{
		ft_putstr("usage: ");
		ft_putstr(name_of_program);
		ft_putstr(" [OPTIONS] < map_file\n");
		ft_putstr("Options:\n");
		ft_putstr("\t--steps     show the number of lines of instructions\n");
		ft_putstr("\t--color     draw the output in different colors\n");
		ft_putstr("\t--paths     show the paths of the found flow\n");
		ft_putstr("\t--flows     show found flows\n");
		ft_putstr("\t--short     show only instructions without a map\n");
		ft_putstr("\t--multi     calculate multi maps at once\n");
		ft_putstr("\t            ");
		ft_putstr(name_of_program);
		ft_putstr(" --multi {map_file_0} {map_file_1} ... {map_file_n}\n");
		exit(1);
	}
}
