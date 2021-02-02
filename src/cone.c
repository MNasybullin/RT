/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:05:29 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/06 18:21:31 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		inter_cone_disc(t_disc *d, t_ray ray2, t_x_t *x, t_cone *s)
{
	d->a = (ray2.d.c[0] * ray2.d.c[0]) - (ray2.d.c[1] * ray2.d.c[1]) +
	(ray2.d.c[2] * ray2.d.c[2]);
	d->b = (2 * ray2.o.c[0] * ray2.d.c[0]) - (2 * ray2.o.c[1] *
	ray2.d.c[1]) + (2 * ray2.o.c[2] * ray2.d.c[2]);
	if (fabs(d->a) <= EPSILON && fabs(d->b) <= EPSILON)
	{
		intersect_caps_cone(s, ray2, x, d->obj_n);
		return (-1);
	}
	d->c = (ray2.o.c[0] * ray2.o.c[0]) - (ray2.o.c[1] * ray2.o.c[1]) +
	(ray2.o.c[2] * ray2.o.c[2]);
	if (fabs(d->a) <= EPSILON && fabs(d->b) > EPSILON)
	{
		x->t[x->max_obj].t = -d->c / (2 * d->b);
		x->t[x->max_obj].obj = d->obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
		intersect_caps_cone(s, ray2, x, d->obj_n);
		return (-1);
	}
	d->disc = (d->b * d->b) - (4 * d->a * d->c);
	return (0);
}

void	disc_cyl_cone(t_disc d, t_ray ray2, t_x_t *x, int obj_n)
{
	d.t0 = ((-d.b - sqrt(d.disc)) / (2 * d.a));
	d.t1 = ((-d.b + sqrt(d.disc)) / (2 * d.a));
	if (d.t0 > d.t1)
	{
		d.temp = d.t0;
		d.t0 = d.t1;
		d.t1 = d.temp;
	}
	d.y0 = ray2.o.c[1] + d.t0 * ray2.d.c[1];
	if (d.min < d.y0 && d.y0 < d.max)
	{
		x->t[x->max_obj].t = d.t0;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
	d.y1 = ray2.o.c[1] + d.t1 * ray2.d.c[1];
	if (d.min < d.y1 && d.y1 < d.max)
	{
		x->t[x->max_obj].t = d.t1;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
}

void	intersect_cone(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	t_ray	ray2;
	t_cone	*s;
	t_disc	d;

	s = (t_cone*)v_s;
	d.obj_n = obj_n;
	ray2 = transform(r, s->transform);
	if (inter_cone_disc(&d, ray2, x, s) == -1)
		return ;
	if (d.disc < 0)
		return ;
	else
	{
		d.min = s->min;
		d.max = s->max;
		disc_cyl_cone(d, ray2, x, obj_n);
	}
	intersect_caps_cone(s, ray2, x, obj_n);
}

int		check_cap_cone(t_ray r, double t, double y)
{
	double	x;
	double	z;

	x = r.o.c[0] + t * r.d.c[0];
	z = r.o.c[2] + t * r.d.c[2];
	if ((x * x) + (z * z) <= fabs(y))
		return (1);
	return (0);
}

void	intersect_caps_cone(t_cone *cone, t_ray r, t_x_t *x, int obj_n)
{
	double	t;

	if (cone->closed == 0 || fabs(r.d.c[1]) <= EPSILON)
		return ;
	t = (cone->min - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->min) == 1)
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
	t = (cone->max - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->max) == 1)
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
}
