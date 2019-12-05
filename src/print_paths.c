/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 00:57:48 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/05 14:55:10 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline size_t	print_line_initialization(char **line, \
													t_path *path, \
													int8_t color)
{
	size_t				len;

	len = path->len_path + (NUMBER_OF_ROOMS(path) - 1) * SEP_PATH_LN + \
			(color ? COLOR_LN + DISCOLOR_END_LN : 1);
	*line = (char*)malloc(len * sizeof(char));
	if (*line == NULL)
		return (0);
	return (len);
}

static inline int8_t	display_color_path(int fd, \
											char *color, \
											t_path *path)
{
	t_node				**node;
	size_t				len;
	char				*line;

	if ((len = print_line_initialization(&line, path, TRUE)) == 0)
		return (FALSE);
	ft_memcpy(line, color, COLOR_LN);
	line += COLOR_LN;
	path->rooms->iter = -1;
	node = ft_vnext_con(path->rooms);
	ft_memcpy(line, (*node)->name->con, (*node)->name->len);
	line += (*node)->name->len;
	node = ft_vnext_con(path->rooms);
	while (node)
	{
		ft_memcpy(line, SEP_PATH, SEP_PATH_LN);
		line += SEP_PATH_LN;
		ft_memcpy(line, (*node)->name->con, (*node)->name->len);
		line += (*node)->name->len;
		node = ft_vnext_con(path->rooms);
	}
	ft_memcpy(line, DISCOLOR_END, DISCOLOR_END_LN);
	write(fd, (line += DISCOLOR_END_LN - len), len);
	ft_memdel((void**)&line);
	return (TRUE);
}

static inline int8_t	display_path(int fd, t_path *path)
{
	t_node				**node;
	size_t				len;
	char				*line;

	if ((len = print_line_initialization(&line, path, FALSE)) == 0)
		return (FALSE);
	path->rooms->iter = -1;
	node = ft_vnext_con(path->rooms);
	ft_memcpy(line, (*node)->name->con, (*node)->name->len);
	line += (*node)->name->len;
	node = ft_vnext_con(path->rooms);
	while (node)
	{
		ft_memcpy(line, SEP_PATH, SEP_PATH_LN);
		line += SEP_PATH_LN;
		ft_memcpy(line, (*node)->name->con, (*node)->name->len);
		line += (*node)->name->len;
		node = ft_vnext_con(path->rooms);
	}
	*line = NL;
	write(fd, (line += 1 - len), len);
	ft_memdel((void**)&line);
	return (TRUE);
}

int8_t					print_paths(int fd, t_vector *colors, t_flows *flows)
{
	t_path				**path;
	long				shift;

	flows->max_flow->paths->iter = -1;
	path = ft_vnext_con(flows->max_flow->paths);
	if (colors)
	{
		shift = PATH_SHIFT_COLOR;
		while (path)
		{
			if (display_color_path(fd, ft_vat(colors, shift++), *path) == FALSE)
				return (FALSE);
			path = ft_vnext_con(flows->max_flow->paths);
		}
	}
	else
	{
		while (path)
		{
			if (display_path(fd, *path) == FALSE)
				return (FALSE);
			path = ft_vnext_con(flows->max_flow->paths);
		}
	}
	return (TRUE);
}
