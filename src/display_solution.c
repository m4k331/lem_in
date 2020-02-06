/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:18:43 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/10 23:16:13 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	get_display_fd(uint8_t opts, t_farm *farm)
{
	char			*name;
	size_t			len;
	int				fd;

	if ((opts & MASK_MULTI) == FALSE)
		return (STDOUT_FILENO);
	if (farm->file == NULL)
		return (-1);
	len = ft_strlen(farm->file);
	name = ft_strnew(len + OUT_FILE_LN);
	if (name == NULL)
		return (-1);
	ft_memcpy(name, farm->file, len);
	ft_memcpy(name + len, OUT_FILE, OUT_FILE_LN);
	fd = open(name, O_CREAT | O_WRONLY, 0666);
	ft_memdel((void**)&name);
	return (fd);
}

static t_display	*create_display(uint8_t opts, \
									t_farm *farm, \
									t_flows *flows)
{
	t_display		*display;

	display = (t_display*)malloc(sizeof(t_display));
	if (display == NULL)
		return (NULL);
	display->fd = get_display_fd(opts, farm);
	if (display->fd == -1)
	{
		ft_memdel((void**)&display);
		return (NULL);
	}
	display->indent = FALSE;
	display->colors = (opts & MASK_COLOR) != FALSE \
					&& (opts & MASK_MULTI) == FALSE ? get_colors(MC) : NULL;
	display->farm = farm;
	display->flows = flows;
	return (display);
}

static inline void	destroy_display(t_display **display)
{
	ft_vdel(&(*display)->colors);
	ft_memdel((void**)display);
}

static inline void	shutting_display(t_display **display, char *msg)
{
	if (msg)
		perror(msg);
	if (*display)
	{
		if (close((*display)->fd) == -1)
			perror("ERROR closing display file");
		destroy_display(display);
	}
}

void				display_solution(uint8_t opts, \
									t_vector *buffer, \
									t_farm *farm, \
									t_flows *flows)
{
	t_display		*display;

	display = create_display(opts, farm, flows);
	if (display == NULL)
	{
		shutting_display(&display, "ERROR create struct display");
		return ;
	}
	if ((opts & MASK_STEPS) != FALSE)
		print_steps(display);
	if ((opts & MASK_PATHS) != FALSE && print_paths(display) == FALSE)
	{
		shutting_display(&display, "ERROR printing paths");
		return ;
	}
	if ((opts & MASK_FLOWS) != FALSE)
		print_flows(display);
	if ((opts & MASK_SHORT) != FALSE || ((opts & 0xFD) & 0xDF) == 0)
	{
		if ((opts & MASK_SHORT) == FALSE)
			print_buffer(display->fd, buffer);
		if (print_short(display) == FALSE)
			shutting_display(&display, "ERROR printing short");
	}
	shutting_display(&display, NULL);
}
