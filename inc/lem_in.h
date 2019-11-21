/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:55:17 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/21 21:40:32 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define VBUFFER_STDIN_SIZE 1024

typedef struct		s_farm
{
	int				ants;
	t_vector		*buffer;
}					t_farm;

int					set_ants(t_farm *farm);
int					set_rooms(t_farm *farm);

void				destroy_buffer(t_vector **buffer);
void				read_stdin(t_vector **buffer);
void				print_buffer(t_vector *buffer);

#endif
