/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 14:11:03 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/13 18:33:14 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_t_minmax	cube_calc(t_ray r2)
{
	t_t_minmax	xt;
	t_t_minmax	yt;
	t_t_minmax	zt;
	t_t_minmax	t;

	xt = check_axis(r2.o.c[0], r2.d.c[0]);
	yt = check_axis(r2.o.c[1], r2.d.c[1]);
	zt = check_axis(r2.o.c[2], r2.d.c[2]);
	t.min = max(xt.min, yt.min, zt.min);
	t.max = min(xt.max, yt.max, zt.max);
	return (t);
}

void		intersect_cube(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	t_cube		*s;
	t_t_minmax	t;
	t_ray		r2;

	s = (t_cube*)v_s;
	r2 = transform(r, s->transform);
	t = cube_calc(r2);
	if (t.min > t.max)
		return ;
	x->t[x->max_obj].t = t.min;
	x->t[x->max_obj].count = 2;
	x->t[x->max_obj].obj = obj_n;
	x->max_obj += 1;
	x->t[x->max_obj].t = t.max;
	x->t[x->max_obj].count = 2;
	x->t[x->max_obj].obj = obj_n;
	x->max_obj += 1;
}

double		min(double x, double y, double z)
{
	double min;

	min = x;
	if (min > y)
		min = y;
	if (min > z)
		min = z;
	return (min);
}

double		max(double x, double y, double z)
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
	double		tmin_numerator;
	double		tmax_numerator;
	double		temp;
	t_t_minmax	t;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (SDL_fabs(direction) >= EPSILON)
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
