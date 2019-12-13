#include "visu.h"
#include "libft.h"

int main(int argc, char **argv)
{
	t_state	state;

	if (init_state(&state) < 0)
		return (-1);
	visu(state);
	return (0);
}
