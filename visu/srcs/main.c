/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:36:11 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/17 16:02:27 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "libft.h"
#include "matrix.h"
#include "event_handling.h"
#include "draw.h"
#include "loops.h"
#include "render.h"

#include <mlx.h>
#include <errno.h>
#include <float.h>

// TODO: FIXME: НЕ ЗАБЫТЬ ДОБАВИТЬ ЗАВИСИМОСТИ В MAKEFILE!!

int	print_invalid_option(char opt, char *prog_name)
{
	ft_putstr("Invalid option: ");
	ft_putchar(opt);
	ft_putchar('\n');
	usage(prog_name);
	return (-1);
}

int	handle_opt(char opt_c, char *prog_name)
{
	int opt;

	opt = 0;
	if (opt_c == 'h')
		exit(usage(prog_name) + 1);
	else if (opt_c == 'c')
		opt |= 1;
	else if (opt_c == 's')
		opt |= 2;
	else
		exit(print_invalid_option(opt_c, prog_name));
	return (opt);
}

int	parse_options(int argc, char **argv)
{
	int	i;
	int	opt;
	int	j;

	opt = 0;
	i = 0;
	while (++i < argc)
		if (argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j])
				opt |= handle_opt(argv[i][j], argv[0]);
			if (j == 1)
				exit(print_invalid_option('-', argv[0]));
		}
		else if (argc - i != 2)
			exit(usage(argv[0]));
		else
			break ;
	return (opt);
}

int	main(int argc, char **argv)
{
	t_state	state;
	int		opt;

	opt = 0;
	errno = 0;
	opt = parse_options(argc, argv);
	if ((opt & 2) && argc > 2)
		state_init(&state, ft_atoi(argv[argc - 2]),
			ft_atoi(argv[argc - 1]), opt & 1);
	else
		state_init(&state, SIZE_X, SIZE_Y, opt & 1);
	visu(&state);
	return (0);
}
