/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:52:22 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/19 17:56:14 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				read_stdin(t_vector **buffer)
{
	t_vector		*data;
	char			*line;
	int				state;

	data = ft_vnew(1024, sizeof(char*));
	state = (data ? 1 : -1);
	while (state > 0)
	{
		state = get_next_line(STDIN_FILENO, &line);
		ft_vpush_back(data, line, sizeof(char*));
	}
	if (state == -1)
	{
		perror("error in read stdin");
		if (data)
			ft_vdel(&data);
		exit(1);
	}
	*buffer = data;
}
