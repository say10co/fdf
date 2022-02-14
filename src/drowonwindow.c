/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowonwindow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:02:38 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 20:55:09 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
int	switch_(int	a)
{
	printf("%d\n", a);
	if (a < 50)
		return (60);
	if (a < 300)
		return (5);
	return (1);
}
void	dda(t_point p0, t_point p1, t_window *win)
{
	int			dx;
	int			dy;
	int			m;
	int			t;	
	float		xscale;
	float		yscale;

	zoom_isometric_shift(&p0, &p1, *win);
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	m = my_abs(dy);
	if (my_abs(dx) > my_abs(dy))
		m = my_abs(dx);
	xscale = (float)dx / m;
	yscale = (float)dy / m;
	while (m-- >= 0)
	{
		if (p0.color == 13720351 && (p0.z != 0 || p1.z != 0))
			p0.color = 14546242;
		t = (int)(p0.y) * win->win_width + (int)(p0.x);
		if (t < (win->win_width * win->win_higth) && (p0.x >= 0 && p0.x <= win->win_width) && (p0.y >= 0 &&  p0.y <= win->win_higth))
			win->img->data[t] = p0.color + win->color_diff;;
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
	image.data = (int *)mlx_get_data_addr(image.img_ptr, &image.bpp, &image.size_l, &image.endian);
	win->img = &image;
	i = 0;
	while (i + 1 <= win->nb_lines)
	{
		k = 0;
		while (k + 1 <= win->line_width)
		{
			if (i + 1 == win->nb_lines)
				dda(matrix[i][k], matrix[i][k], win);
			else
				dda(matrix[i][k], matrix[i + 1][k], win);
			if (k + 1 == win->line_width)
				dda(matrix[i][k], matrix[i][k], win);
			else
				dda(matrix[i][k], matrix[i][k + 1], win);
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img->img_ptr, 0, 0);
}

void	set_default(t_window *base_values)
{
	base_values->shift_x = 2080 / base_values->line_width;
	base_values->shift_y = 2080 / base_values->nb_lines;
	base_values->zoom = switch_(base_values->line_width);
	base_values->z_scale = 1;
	base_values->isometric = 0;
	base_values->angle_of_view = 0.4;
	base_values->color_diff = 500;
}

int	main(int ac, char **av)
{	
	t_point		**matrix;
	t_window	window;

	(void)ac;
	matrix = parser(av[1], &window.nb_lines, &window.line_width);
	window.matrix = matrix;
	set_default(&window);

	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, 2080, 1350, "my_fdf_window");
	window.win_width = 2080;
	window.win_higth = 1350;

	mlx_key_hook(window.win_ptr, key_handler, &window);

	mlx_hook(window.win_ptr, 17, 0, close_, NULL);

	drow(matrix, &window);

	mlx_loop(window.mlx_ptr);
	return (0);
}
