/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:02:36 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 22:24:11 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#include <errno.h>

int		print_error(const char *msg)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(msg, 2);
	if (errno)
		perror("");
	return (-1);
}
