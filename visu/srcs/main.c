/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:36:11 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/12 19:40:54 by rnarbo           ###   ########.fr       */
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

int ft_round(double);
void render(t_state *state);
void do_recalc(t_state *state);

int usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" [-hc] [-s size_x size_y]\n");
	ft_putstr("\t-h - print usage and exit.\n");
	ft_putstr("\t-c - use circle as ant ferm map.\n");
	ft_putstr("\t-s - use size_x size_y as window sizes.\n");
	return (-1);
}

int parse_options(int argc, char **argv)
{
	int	i = 1;
	int	opt = 0;
	int	j;

	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'h')
					exit(usage(argv[0]) + 1);
				else if (argv[i][j] == 'c')
					opt |= 1;
				else if (argv[i][j] == 's')
					opt |= 2;
				else
				{
					ft_putstr("Invalid option: ");
					ft_putchar(argv[i][j]);
					ft_putchar('\n');
					exit(usage(argv[0]));
				}
				j++;
			}
			if (j == 1)
			{
				ft_putstr("Invalid option: -");
				ft_putchar('\n');
				exit(usage(argv[0]));
			}
		}
		else if (argc - i != 2)
			exit(usage(argv[0]));
		else
			break ;
		i++;
	}
	return (opt);
}

int main(int argc, char **argv)
{
	t_state	state;
	int		opt = 0;

	errno = 0;
	opt = parse_options(argc, argv);
	if ((opt & 2) && argc > 2)
		state_init(&state, ft_atoi(argv[argc - 2]), ft_atoi(argv[argc - 1]), opt & 1);
	else
		state_init(&state, SIZE_X, SIZE_Y, opt & 1);
	visu(&state);
	return (0);
}
