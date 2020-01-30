/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:36:11 by rnarbo            #+#    #+#             */
/*   Updated: 2020/01/30 16:56:39 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "libft.h"
#include "matrix.h"
#include "event_handling.h"
#include "draw.h"

#include <mlx.h>
#include <float.h>

// TODO: FIXME: НЕ ЗАБЫТЬ ДОБАВИТЬ ЗАВИСИМОСТИ В MAKEFILE!!

int ft_round(double);
void render(t_state *state, int need_recalc);
void do_recalc(t_state *state);

void put_room(t_state *state, t_room *room)
{
	int i = -3;
	int j;

	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			if (ft_round(room->pos.x) + i > 0 && ft_round(room->pos.x) + i < state->graph.img.x_len &&
				ft_round(room->pos.y) + j > 0 && ft_round(room->pos.y) + j< state->graph.img.y_len)
			{
				if (state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i] <
					room->pos.z + 1)
				{
					putpoint(&state->graph, ft_round(room->pos.x) + i, ft_round(room->pos.y) + j, room->color);
					state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i] = room->pos.z + 1;
				}
				else
				{
					printf("color: %x (%d, %d, %f) depth: %f\n", room->color, i, j, room->pos.z, state->graph.img.depth[ft_round(room->pos.y) + j][ft_round(room->pos.x) + i]);
				}
			}
			j++;
		}
		i++;
	}
}

#include "key_bindings.h"
int key_hook(int keycode, t_state *state)
{
	printf("key pressed (%d)\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
		// exit(free_state(state));
	if (keycode == KEY_Q)
		state->speed = 0;
	if (keycode == KEY_E)
		state->speed += 1;
	// if (keycode == KEY_F)
	// 	mlx_loop_hook(state->graph.mlx_p, &slow_rotate, state);
	// if (keycode == KEY_G)
	// 	mlx_loop_hook(state->graph.mlx_p, 0, 0);
	if (rotate_handle(keycode, state) ||
		shift_handle(keycode, state) ||
		zoom_handle(keycode, state) ||
		proj_handle(keycode, state) ||
		render_handle(keycode, state))
		render(state, 1);
	if (keycode == KEY_H)
	{
		state->menu = !state->menu;
		render(state, 0);
	}
	if (keycode == KEY_G)
	{
		state->step = 0;
		state->step_percent = 0;
		render(state, 0);
	}
	if (keycode == KEY_F)
		state->pause = !state->pause;
	if (keycode == KEY_SPACE)
		state->auto_rotate = !state->auto_rotate;
	return 0;
}

t_point	transform(t_state *state, t_point point)
{
	point = point_init(point.x * state->cam.zoom.x * state->cam.scale,
		point.y * state->cam.zoom.y * state->cam.scale,
		point.z * state->cam.zoom.z * state->cam.scale);
	point = point_init(
		point.x * state->obj.rot_m[0][0] + point.y *
			state->obj.rot_m[0][1] + point.z * state->obj.rot_m[0][2],
		point.x * state->obj.rot_m[1][0] + point.y *
			state->obj.rot_m[1][1] + point.z * state->obj.rot_m[1][2],
		point.x * state->obj.rot_m[2][0] + point.y *
			state->obj.rot_m[2][1] + point.z * state->obj.rot_m[2][2]);
	point = point_init(
		point.x + state->cam.shift.x * state->cam.scale * state->cam.zoom.x,
		point.y + state->cam.shift.y * state->cam.scale * state->cam.zoom.y,
		point.z + state->cam.shift.z * state->cam.scale * state->cam.zoom.z);
	point = state->proj(point, state);
	point = point_init(
		point.x + state->cam.obs.x,
		point.y + state->cam.obs.y,
		point.z + state->cam.obs.z);
	return (point);
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
		state->draw_line(&state->graph,
			transform(state, state->obj.cons[j].r1->pos),
			transform(state, state->obj.cons[j].r2->pos),
			state->obj.cons[j].color);
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

void put_ant(t_state *state, t_point ant_pos, int color)
{
	int i = -2;
	int j;

	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (ft_round(ant_pos.x) + i > 0 && ft_round(ant_pos.x) + i < state->graph.img.x_len &&
				ft_round(ant_pos.y) + j > 0 && ft_round(ant_pos.y) + j < state->graph.img.y_len)
				if (state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(ant_pos.x) + i] <
					ant_pos.z + 1)
				{
					putpoint(&state->graph, ft_round(ant_pos.x) + i, ft_round(ant_pos.y) + j, color);
					// state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(ant_pos.x) + i] = ant_pos.z + 1;
				}
			// else
			// {
				// printf("color: %x (%d, %d, %f) depth: %f\n", color, i, j, ant_pos.z, state->graph.img.depth[ft_round(ant_pos.y) + j][ft_round(room->pos.x) + i]);
			// }
			j++;
		}
		i++;
	}
}

int route_len(t_room **route)
{
	int i = 0;

	while (route[i])
		i++;
	return i;
}

void draw_ants_movement(t_state *state)
{
	int		i;
	int		j;
	t_room	**route;
	t_point	ant_pos;
	t_point start, end;

	i = 0;
	while (i < state->obj.ants_cnt)
	{
		if (state->obj.ants_traces[i].step > state->step)
			break ;
		route = state->obj.routes[state->obj.ants_traces[i].route];
		j = state->step - state->obj.ants_traces[i].step;
		if (j + 1 < route_len(route))
		{
			ant_pos = transform(state, point_init(
				route[j]->pos.x + (route[j + 1]->pos.x - route[j]->pos.x) * state->step_percent / 100,
				route[j]->pos.y + (route[j + 1]->pos.y - route[j]->pos.y) * state->step_percent / 100,
				route[j]->pos.z + (route[j + 1]->pos.z - route[j]->pos.z) * state->step_percent / 100));
			put_ant(state, ant_pos, 0xff00ff);
		}
		i++;
	}
}

unsigned int	menu_intense_reducing(unsigned int i1, unsigned int i2, double transparency_k)
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

#include "utils.h"
void	render_menu_board(t_state *state)
{
	int i;
	int j;

	if (!state->menu)
		return ;
	j = 0;
	while (j < state->graph.img.y_len)
	{
		i = state->graph.img.x_len - 450;
		while (i < state->graph.img.x_len)
		{
			putpoint(&state->graph, i, j, menu_intense_reducing(((unsigned int *)state->graph.img.data)[i + j * state->graph.img.k], 0x131313, 0.15));
			i++;
		}
		j++;
	}
	// mlx_clear_window(state->graph.mlx_p, state->graph.w_p);
	// mlx_put_image_to_window(state->graph.mlx_p, state->graph.w_p, state->graph.img.p, 0, 0);
}

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
	"\tReset:",
	"\t\tTransformations: R",
	"\t\tAnts: G",
	"\tCentrize: 0",
	"\tSpeed:",
	"\t\tTransformations:",
	"\t\t\tIncreese: E",
	"\t\t\tReset: Q",
	NULL
};

void	render_menu(t_state *state)
{
	int h;
	int i;
	int j;
	int shift;

	if (!state->menu)
		return ;
	h = 30;
	i = 0;
	while (help_strs[i])
	{
		shift = 0;
		j = 0;
		while (help_strs[i][j++] == '\t')
			shift += 20;
		mlx_string_put(state->graph.mlx_p, state->graph.w_p,
			state->graph.img.x_len - 420 + shift, h, 0xffffff, help_strs[i]);
		h += 20;
		i++;
	}
}

void	render(t_state *state, int need_recalc)
{
	if (need_recalc)
		do_recalc(state);
	else
		ft_memmove(state->graph.img.data, state->graph.img.duplicate,
			state->graph.img.y_len * state->graph.img.line_size);
	draw_ants_movement(state);
	render_menu_board(state);
	mlx_clear_window(state->graph.mlx_p, state->graph.w_p);
	mlx_put_image_to_window(state->graph.mlx_p, state->graph.w_p, state->graph.img.p, 0, 0);
	render_menu(state);
}

static int	slow_rotate(t_state *state);


int ants_loop(t_state *state)
{
	if (!state->pause)
	{
		state->step_percent++;
		if (state->step_percent > 100)
		{
			state->step_percent = 0;
			state->step++;
		}
		render(state, 0);
	}
	if (state->auto_rotate)
		mlx_loop_hook(state->graph.mlx_p, &slow_rotate, state);
	return 0;
}

#include "math.h"
static int	slow_rotate(t_state *state)
{
	t_point	val;

	if (state->auto_rotate)
	{
		val = point_init(0, M_PI / 360, 0);
		matrix_rotate(state->obj.rot_m, val);
		render(state, 1);
	}
	if (!state->pause)
		mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	return (0);
}

int visu(t_state *state)
{
	state->pr_init(state);
	render(state, 1);
	mlx_hook(state->graph.w_p, 2, 0, &key_hook, state);
	mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	mlx_loop(state->graph.mlx_p);
	return 0;
}

int usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" [-hc] [size_x size_y]\n");
	ft_putstr("\t-h - print usage and exit.\n");
	ft_putstr("\t-c - use circle as ant ferm map.\n");
	return (-1);
}

int parse_options(int argc, char **argv)
{
	int i = 1;
	int opt = 0;

	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			int j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'h')
					exit(usage(argv[0]) + 1);
				else if (argv[i][j] == 'c')
					opt |= 1;
				else if (argv[i][j] == 's')
					opt |= 2;
				else
				{
					ft_putstr("Invalid option: ");
					ft_putchar(argv[i][j]);
					ft_putchar('\n');
					exit(usage(argv[0]));
				}
				j++;
			}
		}
		else if (argc - i != 2)
			exit(usage(argv[0]));
		else
			break ;
		i++;
	}
	return (opt);
}

int main(int argc, char **argv)
{
	t_state	state;
	int		opt = 0;

	opt = parse_options(argc, argv);
	if ((opt & 2) && argc > 2)
		state_init(&state, ft_atoi(argv[argc - 2]), ft_atoi(argv[argc - 1]), opt & 1);
	else
		state_init(&state, SIZE_X, SIZE_Y, opt & 1);
	visu(&state);
	// char *line;
	// int gnl_ret;
	// gnl_ret = get_next_line(0, &line);
	// printf("%d \'%s\'\n", gnl_ret, line);
	return (0);
}
