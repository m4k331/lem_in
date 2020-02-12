#include "visu.h"

void clip_x(t_point *p1, t_point *p2, t_state *state)
{
	t_point tmp;

	if (p1->x < 0)
	{
		tmp.x = 0;
		tmp.y = p1->y - (p1->y - p2->y) / (p1->x - p2->x) * p1->x;
	}
	if (p1->x > state->graph.img.x_len)
	{
		tmp.x = state->graph.img.x_len;
		tmp.y = p1->y - (p1->y - p2->y) / (p1->x - p2->x) * (p1->x - state->graph.img.x_len);
	}
	*p1 = tmp;
}

void clip_y(t_point *p1, t_point *p2, t_state *state)
{
	t_point tmp;

	if (p1->y < 0)
	{
		tmp.y = 0;
		tmp.x = p1->x - (p1->x - p2->x) / (p1->y - p2->y) * p1->y;
	}
	if (p1->y > state->graph.img.y_len)
	{
		tmp.y = state->graph.img.y_len;
		tmp.x = p1->x - (p1->x - p2->x) / (p1->y - p2->y) * (p1->y - state->graph.img.y_len);
	}
	*p1 = tmp;
}

void clipping(t_point *start, t_point *end, t_state *state)
{
	if (start->x < 0 || start->x > state->graph.img.x_len)
		clip_x(start, end, state);
	if (end->x < 0 || end->x > state->graph.img.x_len)
		clip_x(end, start, state);
	if (start->y < 0 || start->y > state->graph.img.y_len)
		clip_y(start, end, state);
	if (end->y < 0 || end->y > state->graph.img.y_len)
		clip_y(end, start, state);
}