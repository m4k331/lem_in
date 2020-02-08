#ifndef EVENT_HANDLING_H
# define EVENT_HANDLING_H

#include "visu.h"

int	render_handle(int keycode, t_state *st);
int	proj_handle(int keycode, t_state *st);
int	zoom_handle(int keycode, t_state *st);
int	shift_handle(int keycode, t_state *state);
int	rotate_handle(int keycode, t_state *state);

int mouse_press(int button, int x, int y, t_state *state);
int mouse_release(int button, int x, int y, t_state *state);

#endif