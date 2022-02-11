#include "includes.h"
#define True 1

int	my_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	shift(t_point *p0, t_point *p1)
{
	int	xshift;
	int	yshift;

	xshift = 180;
	yshift = 180;

	p0->x += xshift;
	p0->y += yshift;
	p1->x += xshift;
	p1->y += yshift;
}

void	zoom_in_out(t_point	*p0, t_point *p1)
{
	int	depth;
	int	ydepth;

	depth = 25;
	ydepth = 15;

	p0->x *= depth;
	p0->y *= ydepth;
	p1->x *= depth;
	p1->y *= ydepth;
}

void	isometric(t_point *p)
{	
	t_point p1 = *p;
	
	p->x = p->x - p->y;
	p->y = (p1.x + p->y) / 2 - p->z;
	
	/*
	float angle = 0.6;
	p->x = (p->x - p->y) * cos(angle);
	p->y = (p1.x + p->y) * sin(angle) - p->z;
	*/

}

void	zoom_isometric_shift(t_point *p0, t_point *p1)
{
	zoom_in_out(p0, p1);
	isometric(p0);
	isometric(p1);
	shift(p0, p1);
}

void	dda(t_point p0, t_point p1, t_window win)
{
	int		dx;
	int		dy;
	int		m;
	float	xscale;
	float	yscale;
	
	zoom_isometric_shift(&p0, &p1);
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	m = my_abs(dy);
	if ( my_abs(dx) > my_abs(dy))
		m = my_abs(dx);
	xscale = (float)dx / m;
	yscale = (float)dy / m;
	if (p0.z || p1.z)
		win.color = 0x00206187;
	while (m-- >= 0)
	{
		mlx_pixel_put(win.mlx_ptr, win.win_ptr, p0.x, p0.y, win.color);	
		p0.x += xscale;
		p0.y += yscale;
	}
}

void	drow(t_point **matrix, t_window win, int y, int x)
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
				dda(matrix[i][k], l, win);
			}
			else
				dda(matrix[i][k], matrix[i+1][k], win);
			if (k + 1 == x)
			{
				l = matrix[i][k];
				dda(matrix[i][k], l, win);
			}
			else
				dda(matrix[i][k], matrix[i][k+1], win);
			k++;

		 }
		i++;
	}
}

int	key_handler(int	k, void	*params)
{
	t_params p;

	k--;
	p = *(t_params *)params;
	mlx_clear_window(p.window.mlx_ptr, p.window.win_ptr);
	drow(p.matrix, p.window, p.y, p.x);
	return (0);
}

int main(int	ac, char **av)
{	
	(void)ac;
	int	y;
	int	x;
	t_point **matrix;
	t_window window;
	t_params	params;
	
	matrix = parser(av[1], &y, &x);

	params.matrix = matrix;

	window.mlx_ptr = mlx_init();

	
	window.win_ptr = mlx_new_window(window.mlx_ptr, 1920,  1080, "my_fdf_window");

	params.window = window;

	params.x = x;

	params.y = y;
	
	mlx_key_hook(window.win_ptr, key_handler, &params);
	
	drow(matrix, window, y, x);
	
	mlx_loop(window.mlx_ptr);
	return (0);
}
