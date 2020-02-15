/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 16:02:31 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 16:05:15 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "utils.h"
#include "render.h"

#include <mlx.h>

unsigned int	menu_intense_reducing
	(unsigned int i1, unsigned int i2, double transparency_k)
{
	unsigned int	a;
	unsigned int	res;
	unsigned char	bias;

	bias = 0;
	res = 0;
	while (bias <= 8 * 3)
	{
		a = (i1 >> bias & 0xff) * transparency_k + (i2 >> bias & 0xff);
		res += (a > 0xff ? 0xff : a) << bias;
		bias += 8;
	}
	return (res);
}

void			render_menu_board(t_state *state, t_point start, t_point end)
{
	int i;
	int j;

	j = start.y;
	while (j < (int)end.y)
	{
		i = start.x;
		while (i < (int)end.x)
		{
			putpoint(&state->graph, i, j,
				menu_intense_reducing(
					((int *)state->graph.img.data)[i + j * state->graph.img.k],
					MENU_BACKGROUND_COLOR, 0.15));
			i++;
		}
		j++;
	}
}

int				route_len(t_room **route)
{
	int i;

	i = 0;
	while (route[i])
		i++;
	return (i);
}

size_t			count_ants_left(t_state *state)
{
	int		i;
	int		j;
	t_room	**route;

	i = 0;
	while (i < state->obj.ants_cnt)
	{
		if (state->obj.ants_traces[i].step > state->dyn.step)
			break ;
		route = state->obj.routes[state->obj.ants_traces[i].route];
		i++;
	}
	return (state->obj.ants_cnt - i);
}

void			put_stat_entry
	(t_state *state, t_point pos, char *ename, int eval)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(eval);
	str = ft_strjoin(ename, tmp);
	mlx_string_put(state->graph.mlx_p, state->graph.w_p,
		pos.x, pos.y, TEXT_COLOR, str);
	free(tmp);
	free(str);
}
