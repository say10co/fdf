/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowonwindow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:02:38 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/12 16:55:10 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	my_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	shift(t_point *p0, t_point *p1, t_point *p_base)
{
	int	xshift;
	int	yshift;

	xshift = p_base->xshift;
	yshift = p_base->yshift;
	p0->x += xshift;
	p0->y += yshift;
	p1->x += xshift;
	p1->y += yshift;
}

void	zoom_in_out(t_point *p0, t_point *p1, t_point p_base)
{
	int	depth;
	int	z_zoom;

	depth = p_base.depth;
	z_zoom = p_base.z_z;
	p0->x *= depth;
	p0->y *= depth;
	p0->z *= z_zoom;
	p1->x *= depth;
	p1->y *= depth;
	p1->z *= z_zoom;
}

void	isometric(t_point *p, t_point p_base)
{
	float angle;
	t_point p1;
   
	p1	= *p;
	angle = p_base.angle;
	p->x = (p->x - p->y) * cos(angle);
	p->y = (p1.x + p->y) * sin(angle) - p->z;
}

void	zoom_isometric_shift(t_point *p0, t_point *p1,t_point *p_base)
{
	zoom_in_out(p0, p1, *p_base);
	if (p_base->iso)
	{
		isometric(p0, *p_base);
		isometric(p1, *p_base);
	}
	shift(p0, p1, p_base);
}

void	dda(t_point p0, t_point p1, t_window win, t_point *p_base)
{
	int		dx;
	int		dy;
	int		m;
	float	xscale;
	float	yscale;
	
	zoom_isometric_shift(&p0, &p1, p_base);
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	m = my_abs(dy);
	if ( my_abs(dx) > my_abs(dy))
		m = my_abs(dx);
	xscale = (float)dx / m;
	yscale = (float)dy / m;
	if (p0.z)
		win.color = 0x00FFA500;
	if (p1.z)
		win.color = 0x009735AB;
	while (m-- >= 0)
	{
		mlx_pixel_put(win.mlx_ptr, win.win_ptr, p0.x, p0.y, win.color);	
		p0.x += xscale;
		p0.y += yscale;
	}
}

void	drow(t_point **matrix, t_window win, int y, int x, t_point *p_base)
{
	int	i;
	int	k;
	t_point l;
	
	i = 0;
	win.color = 0x00FFFFFF;
	while (i + 1 <= y)
	{
		k = 0;
		while (k + 1 <= x)
		{
			if (i + 1 == y)
			{
				l = matrix[i][k];
				dda(matrix[i][k], l, win, p_base);
			}
			else
				dda(matrix[i][k], matrix[i+1][k], win, p_base);
			if (k + 1 == x)
			{
				l = matrix[i][k];
				dda(matrix[i][k], l, win, p_base);
			}
			else
				dda(matrix[i][k], matrix[i][k+1], win, p_base);
			k++;

		 }
		i++;
	}
}

void	set_default(t_point *p_base)
{
	p_base->xshift = 200;
	p_base->yshift = 10;
	p_base->depth = 15;
	p_base->z_z = 1;
	p_base->iso = 1;
	p_base->angle = 0.4;
}

/*
int	key_handler(int	k, void	*params)
{
	t_params p;
	
	p = *(t_params *)params;


	if (k == up)
		p.v->yshift -= 10;
	if (k == down)
		p.v->yshift += 10;
	if (k == left)
		p.v->xshift -= 10;
	if (k == right)
		p.v->xshift += 10;
	if (k == zoom_out)
		p.v->depth += 10;
	if (k == zoom_in && p.v->depth -10 > 0)
		p.v->depth -= 10;
	if (k == reset)
		set_default(p.v);
	if (k == z_up)
		p.v->z_z += 1;
	if (k == z_down)
		p.v->z_z -= 1;
	if (k == tow_d)
		p.v->iso = !(p.v->iso);
	if (k == escap)
	{
		mlx_clear_window(p.window.mlx_ptr, p.window.win_ptr);
		exit(0);
	}
	if (k == rotate_right)
		p.v->angle += 0.1;
	if (k == rotate_left)
		p.v->angle -= 0.1;

	mlx_clear_window(p.window.mlx_ptr, p.window.win_ptr);
	drow(p.matrix, p.window, p.y, p.x, p.v);
	return (0);
}

int	close_(void 	*null)
{
	(void)(null);
	exit(0);
}	
*/
int main(int	ac, char **av)
{	
	(void)ac;
	int	y;
	int	x;
	t_point **matrix;
	t_window window;
	t_params	params;
	t_point		p_base;
	
	set_default(&p_base);
	params.v = &p_base;
	matrix = parser(av[1], &y, &x);
	params.matrix = matrix;
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, 30 * x , 30 * y, "my_fdf_window");
	p_base.sizex = x*30;
	p_base.sizey = y*30;
	params.window = window;
	params.x = x;
	params.y = y;
	mlx_key_hook(window.win_ptr, key_handler, &params);
	mlx_hook(window.win_ptr, 17, 0, close_, NULL);
	drow(matrix, window, y, x, &p_base);
	mlx_loop(window.mlx_ptr);
	return (0);
}
