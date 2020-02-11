/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:36:11 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/11 15:48:51 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "libft.h"
#include "matrix.h"
#include "event_handling.h"
#include "draw.h"
#include "loops.h"

#include <mlx.h>
#include <errno.h>
#include <float.h>

// TODO: FIXME: НЕ ЗАБЫТЬ ДОБАВИТЬ ЗАВИСИМОСТИ В MAKEFILE!!

int ft_round(double);
void render(t_state *state);
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
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_Q)
		state->speed = 0;
	if (keycode == KEY_E)
		state->speed += 1;
	if (rotate_handle(keycode, state) ||
		zoom_handle(keycode, state) ||
		proj_handle(keycode, state) ||
		render_handle(keycode, state))
		state->image_changed = 1;
	if (keycode == KEY_H)
		state->menu = !state->menu;
	if (keycode == KEY_G)
	{
		state->step = 0;
		state->step_percent = 0;
		state->pause = 0;
		state->time = 0;
	}
	if (keycode == KEY_F)
		state->pause = !state->pause;
	if (keycode == KEY_SPACE)
		state->auto_rotate = !state->auto_rotate;
	if (keycode == KEY_TILDA)
		state->stat = !state->stat;
	if (keycode == KEY_PAGE_UP)
		state->ant_speed = state->ant_speed > 10 ? 10 : state->ant_speed + 0.1;
	if (keycode == KEY_PAGE_DOWN)
		state->ant_speed = state->ant_speed < 0.2 ? 0.2 : state->ant_speed - 0.1;
	if (keycode == KEY_PAGE_DOWN || keycode == KEY_PAGE_UP)
		state->time = 0;
	if (keycode == KEY_P)
		state->draw_line = &draw_no_line;
	render(state);
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
		point.x + state->cam.shift.x,
		point.y + state->cam.shift.y,
		point.z + state->cam.shift.z);
	point = state->proj(point, state);
	point = point_init(
		point.x + state->cam.obs.x,
		point.y + state->cam.obs.y,
		point.z + state->cam.obs.z);
	return (point);
}

// i f n ot ( x1<xmin and x2<xmin ) and n ot ( x1>xmax and x2>xmax ) t h e n
// i f n ot ( y1<ymin and y2<ymin ) and n ot ( y1>ymax and y2>ymax ) t h e n
// x [ 1 ] = x1
// y [ 1 ] = y1
// x [ 2 ] = x2
// y [ 2 ] = y2
// i =1
// r e p e a t
// i f x [ i ] < xmin t h e n
// x [ i ] = xmin
// y [ i ] = ( ( y2−y1 ) / ( x2−x1 ) )∗( xmin−x1 )+ y1
// e l s e i f x [ i ] > xmax t h e n
// x [ i ] = xmax
// y [ i ] = ( ( y2−y1 ) / ( x2−x1 ) )∗( xmax−x1 )+ y1
// end i f
// i f y [ i ] < ymin t h e n
// y [ i ] = ymin
// x [ i ] = ( ( x2−x1 ) / ( y2−y1 ) )∗( ymin−y1 )+ x1
// e l s e i f y [ i ] > ymax t h e n
// y [ i ] = ymax
// x [ i ] = ( ( x2−x1 ) / ( y2−y1 ) )∗( ymax−y1 )+ x1
// end i f
// i = i + 1
// u n t i l i>2
// i f n ot ( x[1]<xmin and x[2]<xmin ) t h e n
// i f n ot ( x[1]>xmax and x[2]>xmax ) t h e n
// d rawLi ne ( x [ 1 ] , y [ 1 ] , x [ 2 ] , y [ 2 ] )
// end i f
// end i f
// end i f
// end i f

void fast_clipping(t_point *start, t_point *end, t_state *state)
{
	t_point	p[2];
	int		i;

	if (!(start->x < 0 && end->x < 0) && !(start->x > state->graph.img.x_len && end->x > state->graph.img.x_len))
		if (!(start->y < 0 && end->y < 0) && !(start->y > state->graph.img.y_len && end->y > state->graph.img.y_len))
		{
			p[0] = *start;
			p[1] = *end;
			i = 0;
			while (i < 2)
			{
				if (p[i].x < 0)
				{
					p[i].x = 0;
					p[i].y = ((end->y - start->y) / (end->x - start->x)) * (start->x) + start->y;
				} else if (p[i].x > state->graph.img.x_len)
				{
					p[i].x = state->graph.img.x_len;
					p[i].y = ((end->y - start->y) / (end->x - start->x)) * (state->graph.img.x_len - start->x) + start->y;
				}
				if (p[i].y < 0)
				{
					p[i].x = ((end->x - start->x) / (end->y - start->y)) * (start->y) + start->x;
					p[i].y = 0;
				} else if (p[i].y > state->graph.img.y_len)
				{
					p[i].x = ((end->x - start->x) / (end->y - start->y)) * (state->graph.img.y_len - start->y) + start->x;
					p[i].y = state->graph.img.y_len;
				}
				i++;
			}
			*start = p[0];
			*end = p[1];
		}
}

#include "projections.h"
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
		fast_clipping(&start, &end, state); // TODO: doesn't work
		if (state->proj != persp_proj || (state->proj == persp_proj &&
			(start.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale || end.z < FOCUS_SHIFT_K * state->obj.radius * state->cam.scale)))
			state->draw_line(&state->graph,
				transform(state, state->obj.cons[j].r1->pos),
				transform(state, state->obj.cons[j].r2->pos),
				state->obj.cons[j].color);
	}
	j = -1;
	while (++j < state->obj.rooms_cnt)
	{
		room = state->obj.rooms[j];
		room.pos = transform(state, state->obj.rooms[j].pos);
		put_room(state, &room);
	}
	// dprintf(1, "\n");
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

size_t	count_ants_left(t_state *state)
{
	int i;
	int j;
	t_room **route;

	i = 0;
	while (i < state->obj.ants_cnt)
	{
		if (state->obj.ants_traces[i].step > state->step)
			break ;
		route = state->obj.routes[state->obj.ants_traces[i].route];
		i++;
	}
	return (state->obj.ants_cnt - i);
}

int get_ant_color(int j)
{
	int col;

	col = 0xff00ff;
	col =	((int)((col & 0xff) * (double)(j % 20 + 10) / 30)) +
			((int)(((col >> 4) & 0xff) * (double)(j % 20 + 10) / 30) << 8) +
			((int)(((col >> 8) & 0xff) * (double)(j % 20 + 10) / 30) << 16);
	return (col);
}

void draw_ants_movement(t_state *state)
{
	int		i;
	int		j;
	t_room	**route;
	t_point	ant_pos;
	char	flag;
	// t_point start, end;

	i = 0;
	flag = 1;
	while (i < state->obj.ants_cnt)
	{
		if (state->obj.ants_traces[i].step > state->step)
			break ;
		route = state->obj.routes[state->obj.ants_traces[i].route];
		j = state->step - state->obj.ants_traces[i].step;
		// int col = get_ant_color(j);
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
void	render_menu_board(t_state *state, t_point start, t_point end)
{
	int i;
	int j;

	j = start.y;
	while (j < (int)end.y)
	{
		i = start.x;
		while (i < (int)end.x)
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

void put_stat_entry(t_state *state, t_point pos, char *ename, int eval)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(eval);
	str = ft_strjoin(ename, tmp);
	mlx_string_put(state->graph.mlx_p, state->graph.w_p,
		pos.x, pos.y, 0xffffff, str);
	free(tmp);
	free(str);
}

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

// ds = 50 * (sin(pi / 100 * v * (t + 1) - pi / 2) - sin(pi / 100 * v * t - pi / 2))
// 2 * sin(pi / 100 * v / 2) * cos((pi / 100 * v * (2t + 1) - pi) / 2)

int visu(t_state *state)
{
	state->pr_init(state);
	state->image_changed = 1;
	render(state);
	mlx_hook(state->graph.w_p, 2, 0, &key_hook, state);
	mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	mlx_hook(state->graph.w_p, 4, 0, &mouse_press, state);
	mlx_hook(state->graph.w_p, 5, 0, &mouse_release, state);
	mlx_loop(state->graph.mlx_p);
	return 0;
}

int usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" [-hc] [-s size_x size_y]\n");
	ft_putstr("\t-h - print usage and exit.\n");
	ft_putstr("\t-c - use circle as ant ferm map.\n");
	ft_putstr("\t-s - use size_x size_y as window sizes.\n");
	return (-1);
}

int parse_options(int argc, char **argv)
{
	int	i = 1;
	int	opt = 0;
	int	j;

	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
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
			if (j == 1)
			{
				ft_putstr("Invalid option: -");
				ft_putchar('\n');
				exit(usage(argv[0]));
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

	errno = 0;
	opt = parse_options(argc, argv);
	if ((opt & 2) && argc > 2)
		state_init(&state, ft_atoi(argv[argc - 2]), ft_atoi(argv[argc - 1]), opt & 1);
	else
		state_init(&state, SIZE_X, SIZE_Y, opt & 1);
	visu(&state);
	return (0);
}
