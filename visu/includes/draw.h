#ifndef DRAW_H
# define DRAW_H

# include "visu.h"

void	putpoint(t_graphics *graph_p, int x, int y, unsigned int color);
void	bresenham(t_graphics *graph_p, t_point start, t_point end, unsigned int line_color);
void	xiolin_wu(t_graphics *graph_p, t_point start, t_point end, unsigned int line_color);

#endif