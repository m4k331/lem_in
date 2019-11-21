/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:52:22 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 01:13:21 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				read_stdin(t_vector **buffer)
{
	t_str			*str;
	char			*con;
	int				len;

	len = 0;
	*buffer = ft_vnew(VBUFFER_STDIN_SIZE * sizeof(t_str*), sizeof(t_str*));
	int fd = open("/Users/ahugh/lem_in_gh/mp", O_RDONLY);
	while (*buffer)
	{
		len = get_next_line(fd, &con);
		if (len == -1)
			break ;
		if (con == NULL)
			break ;
		str = ft_tstrbuilt(con, len++);
		if (str == NULL)
			break ;
		if (ft_vpush_back(*buffer, &str, sizeof(t_str*)) == FALSE)
			break ;
	}
	close(fd);
	if (*buffer == NULL || len != 0)
	{
		destroy_buffer(buffer);
		perror("ERROR in read stdin");
		exit(1);
	}
}
