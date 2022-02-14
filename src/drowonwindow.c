/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowonwindow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:02:38 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 22:27:39 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	put_image(t_window *win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
		win->img->img_ptr, 0, 0);
}

void	dda(t_point p0, t_point p1, t_window *win)
{
	float		xscale;
	float		yscale;

	zoom_isometric_shift(&p0, &p1, *win);
	win->slop = my_abs(p1.y - p0.y);
	if (my_abs(p1.x - p0.x) > my_abs(p1.y - p0.y))
		win->slop = my_abs(p1.x - p0.x);
	xscale = (float)(p1.x - p0.x) / win->slop;
	yscale = (float)(p1.y - p0.y) / win->slop;
	while ((win->slop)-- >= 0)
	{
		win->t = (int)(p0.y) *win->win_width + (int)(p0.x);
		if (p0.color == DEFAULT_COLOR && (p0.z != 0 || p1.z != 0))
			p0.color = ORANGE;
		if (win->t < (win->win_width * win->win_higth)
			&& (p0.x >= 0 && p0.x <= win->win_width)
			&& (p0.y >= 0 && p0.y <= win->win_higth))
			win->img->data[win->t] = p0.color + win->color_diff;
		if (win->change_color)
			win->color_diff += 100;
		p0.x += xscale;
		p0.y += yscale;
	}
}

void	drow(t_point **matrix, t_window *win)
{
	int		i;
	int		k;
	t_img	image;

	image.img_ptr = mlx_new_image(win->mlx_ptr, win->win_width, win->win_higth);
	image.data = (int *)mlx_get_data_addr(image.img_ptr,
			&image.bpp, &image.size_l, &image.endian);
	win->img = &image;
	i = -1;
	while (++i + 1 <= win->nb_lines)
	{
		k = -1;
		while (++k + 1 <= win->line_width)
		{
			if (i + 1 == win->nb_lines)
				dda(matrix[i][k], matrix[i][k], win);
			else
				dda(matrix[i][k], matrix[i + 1][k], win);
			if (k + 1 == win->line_width)
				dda(matrix[i][k], matrix[i][k], win);
			else
				dda(matrix[i][k], matrix[i][k + 1], win);
		}
	}
	put_image(win);
}

void	set_default(t_window *base_values)
{
	base_values->shift_x = 2080 / base_values->line_width;
	base_values->shift_y = 2080 / base_values->nb_lines;
	base_values->zoom = switch_(base_values->line_width);
	base_values->z_scale = 1;
	base_values->isometric = 0;
	base_values->angle_of_view = 0.4;
	base_values->color_diff = 0;
	base_values->change_color = 0;
}

int	main(int ac, char **av)
{	
	t_point		**matrix;
	t_window	win;

	(void)ac;
	matrix = parser(av[1], &win.nb_lines, &win.line_width);
	win.matrix = matrix;
	set_default(&win);
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, 2080, 1350, "my_fdf_window");
	win.win_width = 2080;
	win.win_higth = 1350;
	mlx_key_hook(win.win_ptr, key_handler, &win);
	mlx_hook(win.win_ptr, 17, 0, close_, NULL);
	drow(matrix, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
