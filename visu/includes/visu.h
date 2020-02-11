/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:34:37 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/11 12:31:50 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <stddef.h>
# include <stdint.h>
# include "libft.h"
// # include "ft_dlst.h"

// # define SIZE_X 100
// # define SIZE_Y 100

# define SIZE_X 1280
# define SIZE_Y 800

# define MIN_WIN_SIZE_X 450
# define MIN_WIN_SIZE_Y 600

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
	char			type; // 1 - start, 2 - end, 0 - regular
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
}				t_camera;

// typedef struct		s_node
// {
// 	t_str			*name;
// 	struct s_node	*predecessor;
// 	t_dict			*edge;
// 	int64_t			potential;
// 	int64_t			delta;
// 	uint8_t			marks;
// }					t_node;

// typedef struct		s_farm
// {
// 	int64_t			ants;
// 	t_dict			*nodes;
// 	t_node			*start;
// 	t_node			*end;
// 	char			*file;
// 	int8_t			direct;
// }					t_farm;

typedef t_point	t_proj		(t_point point, void *state);
typedef void	t_proj_init	(void *state);
typedef void	t_draw_line	(void *state, t_point start, t_point end, uint32_t color);

typedef struct	s_state
{
	t_graphics		graph;

	int				step;
	double			step_percent;

	t_obj			obj;
	t_camera		cam;

	int				pause;
	int				auto_rotate;
	int				speed;
	double			ant_speed;
	int				time;
	int				menu;
	int				stat;

	char			image_changed;
	t_point			prev_mouse_pos;

	t_proj			*proj;
	t_proj_init		*pr_init;
	t_draw_line		*draw_line;
}				t_state;

int				init_state(t_state *state); // TODO: move
int				visu(t_state *state);

int				usage(char *prog_name);
int				print_error(const char *msg);

t_point			point_init(double x, double y, double z);

# define printf(x, ...)

#endif
