/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:52:22 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** creates a buffer and writes to it line by line data read from fd
** if successful returns a buffer otherwise zero
*/

t_vector			*get_fd_buffer(int fd)
{
	t_vector		*buffer;
	t_str			*str;
	char			*con;
	int				len;

	buffer = ft_vnew((VBUFFER_SIZE) * sizeof(t_str*), sizeof(t_str*));
	while (buffer)
	{
		len = get_next_line(fd, &con);
		if (len == -1)
			break ;
		if (con == NULL)
			return (buffer);
		str = ft_tstrbuilt(con, len);
		if (str == NULL)
			break ;
		if (ft_vpush_back(buffer, &str, sizeof(t_str*)) == FALSE)
			break ;
	}
	destroy_buffer(&buffer);
	return (NULL);
}
