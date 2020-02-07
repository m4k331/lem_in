/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:20:26 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t			print_line_initialization(char **line, \
												t_path *path, \
												int8_t color)
{
	const int			ants_len = ft_numlen(path->ants, 10);
	size_t				size;

	size = (PREFIX_PATH_LN + ants_len + SUFFIX_PATH_LN + \
				path->len_path + (path->rooms->head - 1) * SEP_PATH_LN + \
				(color ? COLOR_LN + DISCOLOR_END_LN : 1)) * sizeof(char);
	*line = (char*)malloc(size);
	if (*line == NULL)
		return (0);
	return (size);
}

static inline void		insert_count_ants_inline(char **line, long ants)
{
	int					len;

	ft_memcpy(*line, PREFIX_PATH, PREFIX_PATH_LN);
	*line = (*line) + PREFIX_PATH_LN;
	len = insert_number_inline(*line, ants);
	*line = (*line) + len;
	ft_memcpy(*line, SUFFIX_PATH, SUFFIX_PATH_LN);
	*line = (*line) + SUFFIX_PATH_LN;
}

static inline void		insert_first_node_inline(char **line, t_path *path)
{
	t_node				**node;

	path->rooms->iter = -1;
	node = ft_vnext_con(path->rooms);
	ft_memcpy(*line, (*node)->name->con, (*node)->name->len);
	*line = (*line) + (*node)->name->len;
}

int8_t					display_color_path(int fd, char *color, t_path *path)
{
	t_node				**node;
	char				*line;
	size_t				len;

	len = print_line_initialization(&line, path, TRUE);
	if (line == NULL)
		return (FALSE);
	ft_memcpy(line, color, COLOR_LN);
	line += COLOR_LN;
	insert_count_ants_inline(&line, path->ants);
	insert_first_node_inline(&line, path);
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
	line += DISCOLOR_END_LN - len;
	write(fd, line, len);
	ft_memdel((void**)&line);
	return (TRUE);
}

int8_t					display_path(int fd, t_path *path)
{
	t_node				**node;
	size_t				len;
	char				*line;

	len = print_line_initialization(&line, path, FALSE);
	if (line == NULL)
		return (FALSE);
	insert_count_ants_inline(&line, path->ants);
	insert_first_node_inline(&line, path);
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
	line++;
	line -= len;
	write(fd, line, len);
	ft_memdel((void**)&line);
	return (TRUE);
}
