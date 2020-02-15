/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:37 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 14:27:45 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <stddef.h>
# include <stdint.h>
# include "libft.h"

# define SIZE_X 1280
# define SIZE_Y 800

# define MIN_WIN_SIZE_X 450
# define MIN_WIN_SIZE_Y 600

# define ANT_COLOR 0xff00ff
# define REGULAR_ROOM_COLOR 0xff00
# define START_ROOM_COLOR 0xff
# define END_ROOM_COLOR 0xff0000
# define TRACE_COLOR 0xffff
# define LINE_COLOR 0xffffff

typedef struct	s_img
{
	void			*p;
	char			*data;
	char			*duplicate;
	int				bpp;
	int				line_size;
	int				endian;
	int				k;
	int				x_len;
	int				y_len;
	double			**depth;
}				t_img;

typedef struct	s_graphics
{
	void			*mlx_p;
	void			*w_p;
	t_img			img;
}				t_graphics;

typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
}				t_point;

typedef struct	s_room
{
	char			*name;
	t_point			pos;
	char			type;
	unsigned int	color;
}				t_room;

typedef	struct	s_conn
{
	t_room			*r1;
	t_room			*r2;
	unsigned int	color;
}				t_conn;

typedef struct	s_trace
{
	size_t			step;
	int				route;
}				t_trace;

typedef struct	s_obj
{
	double		rot_m[3][3];
	double		radius;

	t_room		*rooms;
	size_t		rooms_cnt;

	t_conn		*cons;
	size_t		cons_cnt;

	t_trace		*ants_traces;
	size_t		ants_cnt;

	t_room		***routes;
	size_t		routes_cnt;
}				t_obj;

typedef struct	s_camera
{
	t_point		obs;
	t_point		shift;
	double		scale;
	t_point		zoom;
	int			speed;
}				t_camera;

typedef t_point	t_proj		(t_point point, void *state);
typedef void	t_proj_init	(void *state);
typedef void	t_draw_line
	(void *state, t_point start, t_point end, uint32_t color);

typedef struct	s_dynamic
{
	char		pause;
	char		menu;
	char		stat;
	char		auto_rotate;
	double		ant_speed;
	int			time;
	int			step;
	double		step_percent;
	char		image_changed;
	t_point		prev_mouse_pos;
}				t_dynamic;

typedef struct	s_state
{
	t_graphics		graph;

	t_obj			obj;
	t_camera		cam;
	t_dynamic		dyn;

	t_proj			*proj;
	t_proj_init		*pr_init;
	t_draw_line		*draw_line;
}				t_state;

int				init_state(t_state *state);
int				visu(t_state *state);

int				usage(char *prog_name);
int				print_error(const char *msg);

t_point			point_init(double x, double y, double z);

#endif
