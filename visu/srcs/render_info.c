#include "visu.h"
#include "render.h"

#include <mlx.h>

const char *help_strs[] = 
{
	"HELP:",
	"\tShow / hide help (this): H",
	"\tRotate: Arrows",
	"\tFreeze ants: F",
	"\tAuto rotate: SPACE",
	"\tZoom: + -",
	"\tScale Z: < >",
	"\tScale X and Y: [ ]",
	"\tProjections: 1-4",
	"\t\tz(x): 1",
	"\t\ty(x): 2",
	"\t\tIsometric: 3",
	"\t\tPerspective : 4",
	"\tLine algorithm:",
	"\t\tBresenham: B",
	"\t\tXiolin Wu: X",
	"\t\tPoints: P",
	"\tReset:",
	"\t\tTransformations: R",
	"\t\tAnts: G",
	"\tCentrize: 0",
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
	int		h;
	char	*str;
	char	*tmp;
	int		i;
	t_room	**route;
	int		j;

	h = start.y + 30;
	mlx_string_put(state->graph.mlx_p, state->graph.w_p,
		start.x + 30, h, 0xff00, "STATISTICS:");
	h += 20;
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Ants number: ", state->obj.ants_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Ants in start room: ", count_ants_left(state));
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Rooms number: ", state->obj.rooms_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Connections number: ", state->obj.cons_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Routes number: ", state->obj.routes_cnt);
	put_stat_entry(state, point_init(start.x + 30, h += 20, 0), "    Step: ", state->step + 1); // TODO:
}

void	render_menu(t_state *state, t_point start)
{
	int h;
	int i;
	int j;
	int shift;

	h = start.y + 30;
	i = 0;
	while (help_strs[i])
	{
		shift = 0;
		j = 0;
		while (help_strs[i][j++] == '\t')
			shift += 40;
		mlx_string_put(state->graph.mlx_p, state->graph.w_p,
			start.x + 30 + shift, h, i == 0 ? 0xff00 : 0xffffff, help_strs[i]);
		h += 20;
		i++;
	}
}