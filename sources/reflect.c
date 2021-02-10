/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 16:24:47 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/02 20:51:42 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	reflect(t_vec in, t_vec normal)
{
	t_vec	a;
	t_vec	b;

	b = mult(normal, (2 * dot(in, normal)));
	a = sub(in, b);
	return (a);
}

t_color	reflected_color(t_world w, t_comps c, int remaining)
{
	t_ray	reflect_ray;
	t_color	col;

	if (remaining < 1)
		return (color(0, 0, 0));
	if (w.obj_ar[c.obj].m->reflective > 0 && w.obj_ar[c.obj].m->reflective <= 1)
	{
		reflect_ray = set_ray(c.over_point, c.reflectv);
		col = color_at(&w, reflect_ray, remaining - 1);
		return (mult_col(col, w.obj_ar[c.obj].m->reflective));
	}
	else
		return (color(0, 0, 0));
}

/*
** check for internal full reflection
*/

t_color	refracted_color(t_world w, t_comps c, int remaining)
{
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	double	cos_t;
	t_vec	direction;

	if (remaining < 1)
		return (color(0, 0, 0));
	if (w.obj_ar[c.obj].m->transparency == 0)
		return (color(0, 0, 0));
	n_ratio = c.n1 / c.n2;
	cos_i = dot(c.eyev, c.normalv);
	sin2_t = (n_ratio * n_ratio) * (1.0 - (cos_i * cos_i));
	if (sin2_t > 1.0)
		return (color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	direction = sub(mult(c.normalv, (n_ratio * cos_i - cos_t)),
	mult(c.eyev, n_ratio));
	return (mult_col(color_at(&w, set_ray(c.under_point, direction),
	remaining - 1), w.obj_ar[c.obj].m->transparency));
}
