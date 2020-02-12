#include "visu.h"

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