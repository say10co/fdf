/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:45:43 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 22:20:40 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

int	extend_key_handler(int k, t_window *win)
{
	if (k == UP_KEY)
		win->shift_y -= 100;
	else if (k == DOWN_KEY)
		win->shift_y += 100;
	else if (k == LEFT_KEY)
		win->shift_x -= 100;
	else if (k == RIGHT_KEY)
		win->shift_x += 100;
	else if (k == PLUS_KEY)
		win->zoom += 1;
	else if (k == MINUS_KEY)
		win->zoom -= 1;
	else if (k == Q_KEY)
		set_default(win);
	else if (k == C_KEY)
		win->change_color = !(win->change_color);
	else
		return (0);
	return (1);
}

int	key_handler(int k, void *params)
{
	if (k == X_KEY)
		((t_window *)params)->z_scale += 1;
	else if (k == Z_KEY)
		((t_window *)params)->z_scale -= 1;
	else if (k == W_KEY)
		((t_window *)params)->isometric = !(((t_window *)params)->isometric);
	else if (k == A_KEY)
		((t_window *)params)->angle_of_view += 0.1;
	else if (k == S_KEY)
		((t_window *)params)->angle_of_view -= 0.1;
	else if (k == ESCAPE_KEY)
	{
		mlx_clear_window(((t_window *)params)->mlx_ptr,
			((t_window *)params)->win_ptr);
		exit(0);
	}
	else if (extend_key_handler(k, ((t_window *)params)))
		(void)k;
	else
		return (0);
	mlx_clear_window(((t_window *)params)->mlx_ptr,
		((t_window *)params)->win_ptr);
	drow(((t_window *)params)->matrix, ((t_window *)params));
	return (1);
}

int	close_(void *null)
{	
	(void)(null);
	exit(0);
}

int	switch_(int x)
{
	if (x < 50)
		return (60);
	if (x < 300)
		return (5);
	return (2);
}
