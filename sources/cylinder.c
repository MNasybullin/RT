/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 15:08:03 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/06 18:39:11 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cyl	set_cylinder(void)
{
	t_cyl	c;

	c.c = set_v_p(0, 0, 0, 1);
	c.r = 1;
	c.min = -INFINITY;
	c.max = INFINITY;
	c.closed = 0;
	c.transform = identity_matrix();
	c.m = default_material();
	return (c);
}

void	intersect_cyl(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	t_ray	ray2;
	t_cyl	*s;
	t_disc	d;

	s = (t_cyl*)v_s;
	ray2 = transform(r, s->transform);
	d.a = (ray2.d.c[0] * ray2.d.c[0]) + (ray2.d.c[2] * ray2.d.c[2]);
	if (fabs(d.a) <= EPSILON)
	{
		intersect_caps(s, ray2, x, obj_n);
		return ;
	}
	d.b = (2 * ray2.o.c[0] * ray2.d.c[0]) + (2 * ray2.o.c[2] * ray2.d.c[2]);
	d.c = (ray2.o.c[0] * ray2.o.c[0]) + (ray2.o.c[2] * ray2.o.c[2]) - 1;
	d.disc = (d.b * d.b) - (4 * d.a * d.c);
	if (d.disc < 0)
		return ;
	else
	{
		d.min = s->min;
		d.max = s->max;
		disc_cyl_cone(d, ray2, x, obj_n);
	}
	intersect_caps(s, ray2, x, obj_n);
	return ;
}

int		check_cap(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.o.c[0] + t * r.d.c[0];
	z = r.o.c[2] + t * r.d.c[2];
	if ((x * x) + (z * z) <= 1)
		return (1);
	return (0);
}

void	intersect_caps(t_cyl *cyl, t_ray r, t_x_t *x, int obj_n)
{
	double	t;

	if (cyl->closed == 0 || fabs(r.d.c[1]) <= EPSILON)
		return ;
	t = (cyl->min - r.o.c[1]) / r.d.c[1];
	if (check_cap(r, t) == 1)
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
	t = (cyl->max - r.o.c[1]) / r.d.c[1];
	if (check_cap(r, t) == 1)
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
}

int		normal_at_cyl(void *v_s, t_vec world_point, t_vec *n)
{
	t_cyl	*s;
	t_vec	object_point;
	t_vec	object_normal;
	t_vec	world_normal;
	double	dist;

	s = (t_cyl*)v_s;
	object_point = matrix_mult_v_p(s->transform, world_point);
	dist = (object_point.c[0] * object_point.c[0]) +
	(object_point.c[2] * object_point.c[2]);
	if (dist < 1 && object_point.c[1] >= s->max - EPSILON)
		object_normal = set_v_p(0, 1, 0, 0);
	else if (dist < 1 && object_point.c[1] <= s->min + EPSILON)
		object_normal = set_v_p(0, -1, 0, 0);
	else
		object_normal = set_v_p(object_point.c[0], 0, object_point.c[2], 0);
	world_normal = matrix_mult_v_p(matrix_transposing(s->transform),
	object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}
