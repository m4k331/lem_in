/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:55:17 by ahugh             #+#    #+#             */
/*   Updated: 2019/11/22 19:21:11 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "node.h"
# include "room.h"

# define INF (MAX_INT)
# define VBUFFER_STDIN_SIZE 1024U
# define STARTS_WITH_HASH(str) (*(str) == '#')
# define CMD_START "##start"
# define CMD_END "##end"
# define SPACE ' '
# define NULL_TERMINATE '\0'
# define MASK_COMMON 1U
# define MASK_START 2U
# define MASK_END 4U
# define IS_COMMON(x) ((x) & MASK_COMMON)
# define IS_START(x) ((x) & MASK_START)
# define IS_END(x)  ((x) & MASK_END)

typedef struct		s_farm
{
	long			ants;
	t_vector		*buffer;
}					t_farm;

int8_t				set_ants(t_farm *farm);
int8_t				set_rooms(t_farm *farm);

void				destroy_buffer(t_vector **buffer);
void				read_stdin(t_vector **buffer);
void				print_buffer(t_vector *buffer);

#endif
