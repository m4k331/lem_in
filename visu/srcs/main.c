#include "visu.h"
#include "libft.h"

// TODO: FIXME: НЕ ЗАБЫТЬ ДОБАВИТЬ ЗАВИСИМОСТИ В MAKEFILE!!

int main(int argc, char **argv)
{
	t_state	state;

	dprintf(1, "%d\n", argc);
	if (argc != 1 && argc != 3)
		return (-42);//usage(argv[0]));
	if (argc == 4)
		state_init(&state, argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	else
		state_init(&state, argv[1], SIZE_X, SIZE_Y);
//	visu(&state);
	return (0);return (0);
}
