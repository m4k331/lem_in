#include "visu.h"

#include <errno.h>
// #include <string.h>

int print_error(const char *msg)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(msg, 2);
	if (errno)
		perror(": ");
	return (-1);
}