/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:25:20 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/18 03:38:19 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "render.h"

#include <mlx.h>

char *g_help_strs[] =
{
	"HELP:",
	"\tShow / hide help (this): H",
	"\tRotate: Arrows",
	"\tShift: mouse (left button)",
	"\tShift axis Z: mouse (right button)",
	"\tReset: R",
	"\tCentrize: 0",
	"\tFreeze ants: F",
	"\tAuto rotate: SPACE",
	"\tZoom: + -",
	"\tScale Z: < >",
	"\tScale X and Y: [ ]",
	"\tProjections: 1-3",
	"\t\tz(x): 1",
	"\t\ty(x): 2",
	"\t\tIsometric: 3",
	"\t\tPerspective : 4",
	"\t\tAxonometry : 5",
	"\tLine algorithm:",
	"\t\tBresenham: B",
	"\t\tXiolin Wu: X",
	"\t\tPoints: P",
	"\t\tTransformations: R",
	"\t\tAnts: G",
	"\tSpeed:",
	"\t\tAnts: Page up / Page Down",
	"\t\tTransformations:",
	"\t\t\tIncreese: E",
	"\t\t\tReset: Q",
	"\tShow statistics: ~",
	NULL
};

void	render_stat(t_state *state, t_point start)
{
	ssize_t h;

	h = start.y + 30;
	mlx_string_put(state->graph.mlx_p, state->graph.w_p,
		start.x + 30, h, HEADER_TEXT_COLOR, "STATISTICS:");
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Ants number: ", state->obj.ants_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Ants in start room: ", count_ants_left(state));
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Rooms number: ", state->obj.rooms_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Connections number: ", state->obj.cons_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Routes number: ", state->obj.routes_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0),
		"    Step: ", state->dyn.step);
}

void	render_menu(t_state *state, t_point start)
{
	ssize_t h;
	ssize_t i;
	ssize_t j;
	ssize_t shift;

	h = start.y + 30;
	i = 0;
	while (g_help_strs[i])
	{
		shift = 0;
		j = 0;
		while (g_help_strs[i][j++] == '\t')
			shift += 40;
		mlx_string_put(state->graph.mlx_p, state->graph.w_p,
			start.x + 30 + shift, h, i == 0 ?
				HEADER_TEXT_COLOR : TEXT_COLOR, g_help_strs[i]);
		h += 20;
		i++;
	}
}
