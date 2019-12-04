/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_number_inline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:42:30 by ahugh             #+#    #+#             */
/*   Updated: 2019/12/04 21:49:32 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					insert_number_inline(char *line, long num)
{
	long			dup;
	int				len;

	dup = num;
	len = 1;
	while (dup > 9)
	{
		dup /= 10;
		len++;
	}
	dup = len;
	while (dup--)
	{
		line[dup] = (char)((num % 10) + '0');
		num /= 10;
	}
	return (len);
}
