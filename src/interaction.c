/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:12:43 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/14 05:43:14 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	my_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	shift(t_point *p0, t_point *p1, t_window win)
{
	int	xshift;
	int	yshift;

	xshift = win.shift_x;
	yshift = win.shift_y;
	p0->x += xshift;
	p0->y += yshift;
	p1->x += xshift;
	p1->y += yshift;
}

void	zoom_in_out(t_point *p0, t_point *p1, t_window win)
{
	int	zoom;
	int	z_scale;

	zoom = win.zoom;
	z_scale = win.z_scale;
	p0->x *= zoom;
	p0->y *= zoom;
	p0->z *= z_scale;
	p1->x *= zoom;
	p1->y *= zoom;
	p1->z *= z_scale;
}

void	isometric(t_point *p, t_window win)
{
	float	angle;
	t_point	p_org;

	p_org = *p;
	angle = win.angle_of_view;
	p->x = (p->x - p->y) * cos(angle);
	p->y = (p_org.x + p->y) * sin(angle) - p->z;
}

void	zoom_isometric_shift(t_point *p0, t_point *p1, t_window win)
{
	zoom_in_out(p0, p1, win);
	if (win.isometric)
	{
		isometric(p0, win);
		isometric(p1, win);
	}
	shift(p0, p1, win);
}
