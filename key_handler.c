/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:45:43 by adriouic          #+#    #+#             */
/*   Updated: 2022/02/12 17:00:55 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes.h"

void	extend_key_handler(int	k, t_params *p)
{
	if (k == up)
		p->v->yshift -= 10;
	if (k == down)
		p->v->yshift += 10;
	if (k == left)
		p->v->xshift -= 10;
	if (k == right)
		p->v->xshift += 10;
	if (k == zoom_out)
		p->v->depth += 10;
	if (k == zoom_in && p->v->depth -10 > 0)
		p->v->depth -= 10;
	if (k == reset)
		set_default(p->v);
}

int key_handler(int k, void *params)
{
	t_params	p;
	
	p = *(t_params *)params;
	if (k == z_up)
		p.v->z_z += 1;
	if (k == z_down)
		p.v->z_z -= 1;
	if (k == tow_d)
		p.v->iso = !(p.v->iso);
	if (k == rotate_right)
		p.v->angle += 0.1;
	if (k == rotate_left)
		p.v->angle -= 0.1;
	if (k == escap)
	{
		mlx_clear_window(p.window.mlx_ptr, p.window.win_ptr);
		exit(0);
	}
	extend_key_handler(k, &p);
	
	mlx_clear_window(p.window.mlx_ptr, p.window.win_ptr);
	drow(p.matrix, p.window, p.y, p.x, p.v);
	return (0);
}

int	close_(void *null)
{	
	(void)(null);
	exit(0);
}
