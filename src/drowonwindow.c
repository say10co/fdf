/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowonwindow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:02:38 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/13 21:04:40 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	dda(t_point p0, t_point p1, t_window win, t_point *p_base)
{
	int		dx;
	int		dy;
	int		m;
	float		xscale;
	float		yscale;

	int  t;	
	zoom_isometric_shift(&p0, &p1, p_base);
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	m = my_abs(dy);
	if ( my_abs(dx) > my_abs(dy))
		m = my_abs(dx);
	xscale = (float)dx / m;
	yscale = (float)dy / m;
	while (m-- >= 0)
	{
		t = (int)(p0.y) * win.width + (int)(p0.x);
		if ((p0.x >= 0 && p0.x <= win.width) && (p0.y >= 0 &&  p0.y <= win.higth) && t < (win.width * win.width))
			win.img->data[t] = p0.color;
		//mlx_pixel_put(win.mlx_ptr, win.win_ptr, p0.x, p0.y, p0.color);	
		p0.x += xscale;
		p0.y += yscale;
	}
}

void	drow(t_point **matrix, t_window win, int y, int x, t_point *p_base)
{
	int	i;
	int	k;
	t_img	image;

	image.img_ptr = mlx_new_image(win.mlx_ptr, win.width, win.higth);
	image.data = (int *)mlx_get_data_addr(image.img_ptr, &image.bpp, &image.size_l, &image.endian);
	win.img = &image;
	i = 0;
	while (i + 1 <= y)
	{
		k = 0;
		while (k + 1 <= x)
		{
			if (i + 1 == y)
				dda(matrix[i][k], matrix[i][k], win, p_base);
			else
				dda(matrix[i][k], matrix[i+1][k], win, p_base);
			if (k + 1 == x)
				dda(matrix[i][k], matrix[i][k], win, p_base);
			else
				dda(matrix[i][k], matrix[i][k+1], win, p_base);
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr,  win.img->img_ptr, 0,0);
}

void	set_default(t_point *p_base)
{
	p_base->xshift = 100;
	p_base->yshift = 10;
	p_base->depth = 1;
	p_base->z_z = 1;
	p_base->iso = 1;
	p_base->angle = 0.4;
}

int main(int	ac, char **av)
{	
	int		y;
	int		x;
	t_point 	**matrix;
	t_window	 window;
	t_params	params;
	t_point		p_base;



	(void)ac;
	window.color = 0x00FFFFFF;
	set_default(&p_base);
	params.v = &p_base;
	matrix = parser(av[1], &y, &x);
	params.matrix = matrix;
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, 1000 , 1000, "my_fdf_window");
	//----------------//
	window.width = 1000;//40 * x;
	window.higth = 1000;//40 * y;
	//----------------//	
	p_base.sizex = 1000;//x * 40;
	p_base.sizey = 1000;//y * 40;
	params.window = window;
	params.x = x;
	params.y = y;
	mlx_key_hook(window.win_ptr, key_handler, &params);
	mlx_hook(window.win_ptr, 17, 0, close_, NULL);
	drow(matrix, window, y, x, &p_base);
	mlx_loop(window.mlx_ptr);
	return (0);
}
