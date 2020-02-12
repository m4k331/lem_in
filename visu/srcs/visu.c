#include "visu.h"
#include "key_bindings.h"
#include "event_handling.h"
#include "projections.h"
#include "draw.h"
#include "loops.h"

#include <mlx.h>

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

// ds = 50 * (sin(pi / 100 * v * (t + 1) - pi / 2) - sin(pi / 100 * v * t - pi / 2))
// 2 * sin(pi / 100 * v / 2) * cos((pi / 100 * v * (2t + 1) - pi) / 2)

int close_on_red(void *par)
{
	(void)par;
	exit(0);
}

int visu(t_state *state)
{
	state->pr_init(state);
	state->image_changed = 1;
	render(state);
	mlx_hook(state->graph.w_p, 2, 0, &key_hook, state);
	mlx_loop_hook(state->graph.mlx_p, &ants_loop, state);
	mlx_hook(state->graph.w_p, 4, 0, &mouse_press, state);
	mlx_hook(state->graph.w_p, 5, 0, &mouse_release, state);
	mlx_hook(state->graph.w_p, 17, 0, &close_on_red, state);
	mlx_loop(state->graph.mlx_p);
	return 0;
}