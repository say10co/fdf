#include "includes.h"

int     my_abs(int a)
{
        if (a < 0)
                return (-a);
        return (a);
}

void    shift(t_point *p0, t_point *p1, t_point *p_base)
{
        int     xshift;
        int     yshift;

        xshift = p_base->xshift;
        yshift = p_base->yshift;
        p0->x += xshift;
        p0->y += yshift;
        p1->x += xshift;
        p1->y += yshift;
}

void    zoom_in_out(t_point *p0, t_point *p1, t_point p_base)
{
        int     depth;
        int     z_zoom;

        depth = p_base.depth;
        z_zoom = p_base.z_z;
        p0->x *= depth;
        p0->y *= depth;
        p0->z *= z_zoom / 2;
        p1->x *= depth;
        p1->y *= depth;
        p1->z *= z_zoom / 2;
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

void    zoom_isometric_shift(t_point *p0, t_point *p1,t_point *p_base)
{
        zoom_in_out(p0, p1, *p_base);
        if (p_base->iso)
        {
                isometric(p0, *p_base);
                isometric(p1, *p_base);
        }
        shift(p0, p1, p_base);
}
