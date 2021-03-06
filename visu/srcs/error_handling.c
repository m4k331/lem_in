/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:02:36 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 00:48:05 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#include <errno.h>

int		print_error(const char *msg)
{
	ft_putstr_fd("ERROR: ", 2);
	if (errno)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	return (-1);
}

int		usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" [-hc] [-s size_x size_y]\n");
	ft_putstr("\t-h - print usage and exit.\n");
	ft_putstr("\t-c - use circle as ant ferm map.\n");
	ft_putstr("\t-s - use size_x size_y as window sizes.\n");
	return (-1);
}
