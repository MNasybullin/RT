/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:05:29 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/12 19:23:12 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_cone	set_cone()
{
	t_cone	c;

	c.c = set_v_p(0, 0, 0, 1);
	c.r = 1;
	c.min = -INFINITY;
	c.max = INFINITY;
	c.closed = 0;
	c.transform = identity_matrix();
	c.m = default_material();
	return (c);
}

void	intersect_cone(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	t_ray	ray2;
	t_cone	*s;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	temp;
	double	t1;
	double	t0;
	double	y0;
	double	y1;

	s = (t_cone*)v_s;

	ray2 = transform(r, matrix_inverse(s->transform));
	a = (ray2.d.c[0] * ray2.d.c[0]) - (ray2.d.c[1] * ray2.d.c[1]) + (ray2.d.c[2] * ray2.d.c[2]);
	b = (2 * ray2.o.c[0] * ray2.d.c[0]) - (2 * ray2.o.c[1] * ray2.d.c[1]) + (2 * ray2.o.c[2] * ray2.d.c[2]);
	if (fabs(a) <= EPSILON && fabs(b) <= EPSILON)
	{
		intersect_caps_cone(s, ray2, x, obj_n);
		return ;
		//return (x);
	}
	c = (ray2.o.c[0] * ray2.o.c[0]) - (ray2.o.c[1] * ray2.o.c[1]) + (ray2.o.c[2] * ray2.o.c[2]);
	if (fabs(a) <= EPSILON && fabs(b) > EPSILON)
	{
		x->t[x->max_obj].t = -c / (2 * b);
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
		intersect_caps_cone(s, ray2, x, obj_n);
		return ;
		//return (x);
	}
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return ;
		//return (x);
	else
	{
		t0 = ((-b - sqrt(disc)) / (2 * a));
		t1 = ((-b + sqrt(disc)) / (2 * a));
		if (t0 > t1)
		{
			temp = t0;
			t0 = t1;
			t1 = temp;
		}
		y0 = ray2.o.c[1] + t0 * ray2.d.c[1];
		if (s->min < y0 && y0 < s->max)
		{
			x->t[x->max_obj].t = t0;
			x->t[x->max_obj].obj = obj_n;
			x->t[x->max_obj].count = 2;
			x->max_obj += 1;
		}
		y1 = ray2.o.c[1] + t1 * ray2.d.c[1];
		if (s->min < y1 && y1 < s->max)
		{
			x->t[x->max_obj].t = t1;
			x->t[x->max_obj].obj = obj_n;
			x->t[x->max_obj].count = 2;
			x->max_obj += 1;
		}
	}
	intersect_caps_cone(s, ray2, x, obj_n);
	return ;
	//return (x);
}

int	check_cap_cone(t_ray r, double t, double y)
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
		//return (x);
	t = (cone->min - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->min) == 1) //проверка нижней крышки
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
	t = (cone->max - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->max) == 1) // проверка верхней крышки
	{
		x->t[x->max_obj].t = t;
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
	}
	//return (x);
}

int		normal_at_cone(void *v_s, t_vec world_point, t_vec *n)
{
	t_cone	*s;
	t_vec	object_point;
	t_vec   object_normal;
	t_vec	world_normal;
	double	dist;
	double y;

	s = (t_cone*)v_s;
	object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
	dist = (object_point.c[0] * object_point.c[0]) + (object_point.c[2] * object_point.c[2]);
	if (dist < 1 && object_point.c[1] >= s->max - EPSILON)
	{
		object_normal = set_v_p(0, 1, 0, 0);
	}
	else if (dist < 1 && object_point.c[1] <= s->min + EPSILON)
	{
		object_normal = set_v_p(0, -1, 0, 0);
	}
	else
	{
		y = sqrt((object_point.c[0] * object_point.c[0]) + (object_point.c[2] * object_point.c[2]));
		if (object_point.c[1] > 0)
			y = -y;
		object_normal = set_v_p(object_point.c[0], y, object_point.c[2], 0);
	}
	world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}
