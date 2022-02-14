/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:45:43 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 17:37:49 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

int	extend_key_handler(int k, t_window *win)
{
	if (k == up_key)
		win->shift_y -= 100;
	else if (k == down_key)
		win->shift_y += 100;
	else if (k == left_key)
		win->shift_x -= 100;
	else if (k == right_key)
		win->shift_x += 100;
	else if (k == plus_key)
		win->zoom += 1;
	else if (k == minus_key)
		win->zoom -= 1;
	else if (k == q_key)
		set_default(win);
	else if (k == c_key)
		win->color_diff += 500;
	else
		return (0);
	return (1);
}

int	key_handler(int k, void *params)
{
	if (k == x_key)
		((t_window *)params)->z_scale += 1;
	else if (k == z_key)
		((t_window *)params)->z_scale -= 1;
	else if (k == w_key)
		((t_window *)params)->isometric = !(((t_window *)params)->isometric);
	else if (k == a_key)
		((t_window *)params)->angle_of_view += 0.1;
	else if (k == s_key)
		((t_window *)params)->angle_of_view -= 0.1;
	else if (k == escap_key)
	{
		mlx_clear_window(((t_window *)params)->mlx_ptr, ((t_window *)params)->win_ptr);
		exit(0);
	}
	else if (extend_key_handler(k, ((t_window *)params)))
		(void)k;
	else
		return (0);
	mlx_clear_window(((t_window *)params)->mlx_ptr, ((t_window *)params)->win_ptr);
	drow(((t_window *)params)->matrix, ((t_window *)params));
	return (1);
}

int	close_(void *null)
{	
	(void)(null);
	exit(0);
}
