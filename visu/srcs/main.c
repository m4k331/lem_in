#include "visu.h"
#include "libft.h"

int main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2 && argc != 4)
		return (usage(argv[0]));
	if (argc == 4)
		state_init(&state, argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	else
		state_init(&state, argv[1], SIZE_X, SIZE_Y);
	visu(&state);
	return (0);return (0);
}
