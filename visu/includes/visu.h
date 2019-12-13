#ifndef VISU_H
# define VISU_H

# include <stddef.h>
// # include "ft_dlst.h"

// # define SIZE_X 100
// # define SIZE_Y 100

# define SIZE_X 1280
# define SIZE_Y 800

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

// typedef struct	s_room
// {
// 	int				num;
// 	t_point			pos;
// }

// typedef struct	s_way
// {
// 	t_point			*start;
// 	t_point			*end;
// 	unsigned int	color;
// 	char			has_ant;
// 	char			direction;
// }				t_way;

typedef struct	s_obj
{
	double		rot_m[3][3];
	double		radius;

	t_point		*rooms;
	int			rooms_cnt;

	int			*lines;
	uint16_t	*paths;
}				t_obj;

typedef struct	s_camera
{
	t_point	obs;
	t_point	shift;
	double	scale;
	t_point	zoom;
}				t_camera;

typedef t_point	t_proj		(t_point point, void *state);
typedef void	t_proj_init	(void *state);
typedef void	t_draw_line	(void *state, t_path *path, t_step *step);

typedef struct	s_state
{
	t_graphics		graph;

	int				step;
	int				step_percent;
	t_obj			lem_in;

	t_cam			cam;

	char			image_changed;

	t_proj			*proj;
	t_proj_init		*pr_init;
	t_draw_line		*draw_cell;
}				t_state;

t_point			point_init(int x, int y, int z); // TODO: move
int				init_state(t_state *state); // TODO: move
int				visu(t_state *state);

int				usage(char *prog_name);
int				print_error(const char *msg);

#endif
