#include "visu.h"
#include "projections.h"
#include "render.h"

#include <float.h>
#include <mlx.h>

void draw_ants_movement(t_state *state)
{
	int		i;
	int		j;
	t_room	**route;
	t_point	ant_pos;
	char	flag;

	i = 0;
	flag = 1;
	while (i < state->obj.ants_cnt)
	{
		if (state->obj.ants_traces[i].step > state->step)
			break ;
		route = state->obj.routes[state->obj.ants_traces[i].route];
		j = state->step - state->obj.ants_traces[i].step;
		if (j + 1 < route_len(route))
		{
			flag = 0;
			ant_pos = transform(state, point_init(
				route[j]->pos.x + (route[j + 1]->pos.x - route[j]->pos.x) * state->step_percent / 100,
				route[j]->pos.y + (route[j + 1]->pos.y - route[j]->pos.y) * state->step_percent / 100,
				route[j]->pos.z + (route[j + 1]->pos.z - route[j]->pos.z) * state->step_percent / 100));
			put_ant(state, ant_pos, 0xff00ff);
		}
		i++;
	}
	if (flag)
		state->pause = 1;
}

void do_recalc(t_state *state)
{
	int		i;
	int		j;
	t_room	room;

	j = -1;
	ft_memset(state->graph.img.data, 0, state->graph.img.y_len * state->graph.img.line_size);
	while (++j < state->graph.img.y_len && (i = -1) == -1)
		while (++i < state->graph.img.x_len)
			state->graph.img.depth[j][i] = -DBL_MAX;
	j = -1;
	while (++j < state->obj.cons_cnt)
	{
		t_point start, end;
		start = transform(state, state->obj.cons[j].r1->pos);
		end = transform(state, state->obj.cons[j].r2->pos);
		clipping(&start, &end, state); // TODO: doesn't work
		if (state->proj != perspective_proj || (state->proj == perspective_proj &&
			(start.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale || end.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale)))
		{
			if (!(start.x < 0 && end.x < 0))
			if (!(start.x > state->graph.img.x_len && end.x > state->graph.img.x_len))
			{
				state->draw_line(&state->graph,
					start,
					end,
					state->obj.cons[j].color);
				if (fabs(start.x) > 5000 || fabs(end.x) > 5000 || fabs(start.y) > 5000 || fabs(end.y) > 5000)
					dprintf(1, "(%f %f)\n(%f %f)\n\n", start.x, start.y, end.x, end.y);
			}
		}
	}
	j = -1;
	while (++j < state->obj.rooms_cnt)
	{
		room = state->obj.rooms[j];
		room.pos = transform(state, state->obj.rooms[j].pos);
		put_room(state, &room);
	}
	ft_memmove(state->graph.img.duplicate, state->graph.img.data,
		state->graph.img.y_len * state->graph.img.line_size);
}

void	render(t_state *state)
{
	if (state->image_changed)
		do_recalc(state);
	else
		ft_memmove(state->graph.img.data, state->graph.img.duplicate,
			state->graph.img.y_len * state->graph.img.line_size);
	draw_ants_movement(state);
	if (state->menu)
		render_menu_board(state,
			point_init(state->graph.img.x_len - MIN_WIN_SIZE_X, 0, 0),
			point_init(state->graph.img.x_len, state->graph.img.y_len, 0));
	if (state->stat)
		render_menu_board(state, point_init(0, 0, 0),
			point_init(MIN_WIN_SIZE_X, state->graph.img.y_len, 0));
	mlx_clear_window(state->graph.mlx_p, state->graph.w_p);
	mlx_put_image_to_window(state->graph.mlx_p, state->graph.w_p,
		state->graph.img.p, 0, 0);
	if (state->stat)
		render_stat(state, point_init(0, 0, 0));
	if (state->menu)
		render_menu(state,
			point_init(state->graph.img.x_len - MIN_WIN_SIZE_X, 0, 0));
	state->image_changed = 0;
}