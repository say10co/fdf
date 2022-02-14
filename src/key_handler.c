/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:45:43 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 05:48:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	extend_key_handler(int k, t_window *win)
{
	if (k == up)
		win->shift_y -= 100;
	if (k == down)
		win->shift_y += 100;
	if (k == left)
		win->shift_x -= 100;
	if (k == right)
		win->shift_x += 100;
	if (k == zoom_out)
		win->zoom += 1;
	if (k == zoom_in)
		win->zoom -= 1;
	if (k == reset)
		set_default(win);
}

int	key_handler(int k, void *params)
{

	if (k == z_up)
		((t_window *)params)->z_scale += 1;
	if (k == z_down)
		((t_window *)params)->z_scale -= 1;
	if (k == tow_d)
		((t_window *)params)->isometric = !(((t_window *)params)->isometric);
	if (k == rotate_right)
		((t_window *)params)->angle_of_view += 0.1;
	if (k == rotate_left)
		((t_window *)params)->angle_of_view -= 0.1;
	if (k == escap)
	{
		mlx_clear_window(((t_window *)params)->mlx_ptr, ((t_window *)params)->win_ptr);
		exit(0);
	}
	extend_key_handler(k, ((t_window *)params));
	mlx_clear_window(((t_window *)params)->mlx_ptr, ((t_window *)params)->win_ptr);
	drow(((t_window *)params)->matrix, ((t_window *)params));
	return (0);
}

int	close_(void *null)
{	
	(void)(null);
	exit(0);
}
