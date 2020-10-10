/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 14:11:03 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/10 22:19:35 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_cube	set_cube()
{
	t_cube	c;

	c.c = set_v_p(0, 0, 0, 1);
	c.transform = identity_matrix();
	c.m = default_material();
	return (c);
}

t_x_t	intersect_cube(void *v_s, t_ray r, t_x_t x, int obj_n)
{
	t_cube		*s;
	t_t_minmax	xt;
	t_t_minmax	yt;
	t_t_minmax	zt;
	t_t_minmax	t;
	t_ray		r2;

	s = (t_cube*)v_s;
	r2 = transform(r, matrix_inverse(s->transform));

	xt = check_axis(r2.o.c[0], r2.d.c[0]);
	yt = check_axis(r2.o.c[1], r2.d.c[1]);
	zt = check_axis(r2.o.c[2], r2.d.c[2]);

	t.min = max(xt.min, yt.min, zt.min);
	t.max = min(xt.max, yt.max, zt.max);
	if (t.min > t.max)
		return (x);

	x.t[x.max_obj].t = t.min;
	x.t[x.max_obj].count = 2;
	x.t[x.max_obj].obj = obj_n;
	x.max_obj += 1;

	x.t[x.max_obj].t = t.max;
	x.t[x.max_obj].count = 2;
	x.t[x.max_obj].obj = obj_n;
	x.max_obj += 1;
	return (x);
}

double	min(double x, double y, double z)
{
	double min;

	min = x;
	if (min > y)
		min = y;
	if (min > z)
		min = z;
	return (min);
}

double	max(double x, double y, double z)
{
	double max;

	max = x;
	if (max < y)
		max = y;
	if (max < z)
		max = z;
	return (max);
}

t_t_minmax	check_axis(double origin, double direction)
{
	double	tmin_numerator;
	double	tmax_numerator;
	double	temp;
	t_t_minmax t;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		t.min = tmin_numerator / direction;
		t.max = tmax_numerator / direction;
	}
	else
	{
		t.min = tmin_numerator * INFINITY;
		t.max = tmax_numerator * INFINITY;
	}
	if (t.min > t.max)
	{
		temp = t.min;
		t.min = t.max;
		t.max = temp;
	}
	return (t);
}

int		normal_at_cube(void *v_s, t_vec world_point, t_vec *n)
{
	t_cube	*s;
	t_vec	object_point;
	t_vec   object_normal;
	t_vec	world_normal;
	double maxc;

	s = (t_cube*)v_s;
	object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
	maxc = max(fabs(object_point.c[0]), fabs(object_point.c[1]), fabs(object_point.c[2]));
	if (maxc == fabs(object_point.c[0]))
	{
		object_normal = set_v_p(object_point.c[0], 0, 0, 0);
	}
	else if (maxc == fabs(object_point.c[1]))
	{
		object_normal = set_v_p(0, object_point.c[1], 0, 0);
	}
	else
	{
		object_normal = set_v_p(0, 0, object_point.c[2], 0);
	}
	world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}
