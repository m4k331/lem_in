/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <rnarbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:26:53 by rnarbo            #+#    #+#             */
/*   Updated: 2020/02/15 15:31:49 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLING_H
# define EVENT_HANDLING_H

# include "visu.h"

int	render_handle(int keycode, t_state *st);
int	proj_handle(int keycode, t_state *st);
int	zoom_handle(int keycode, t_state *st);
int	shift_handle(int keycode, t_state *state);
int	rotate_handle(int keycode, t_state *state);

int mouse_press(int button, int x, int y, t_state *state);
int mouse_release(int button, int x, int y, t_state *state);

#endif
