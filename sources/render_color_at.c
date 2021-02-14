/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:44:37 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 14:27:04 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_arr	comps_n_calculate_help(t_arr containers, t_t_o curr_i, int size_stack)
{
	int	flag;
	int	bb;

	flag = -1;
	bb = 0;
	while (bb < containers.size)
	{
		if (containers.arr[bb] == curr_i.obj)
			flag = bb;
		bb++;
	}
	if (flag > -1)
	{
		containers.arr[flag] = -1;
		containers = removenull(containers, size_stack);
	}
	else
	{
		containers.arr[containers.size] = curr_i.obj;
		containers.size = containers.size + 1;
	}
	return (containers);
}

t_comps	comps_n_calculate(t_world *w, int hit_obj, t_x_t x, t_comps c)
{
	t_arr	containers;
	int		aa;
	t_t_o	curr_i;

	containers.arr = alloc_int(w->ar_count);
	containers.size = 0;
	aa = 0;
	while (aa < x.max_obj)
	{
		curr_i = x.t[aa];
		if (curr_i.t == x.t[hit_obj].t && curr_i.obj == x.t[hit_obj].obj)
			c.n1 = containers.size == 0 ? 1.0 :
			w->obj_ar[containers.arr[containers.size - 1]].m->refractive_index;
		containers = comps_n_calculate_help(containers, curr_i, w->ar_count);
		if (curr_i.t == x.t[hit_obj].t && curr_i.obj == x.t[hit_obj].obj)
		{
			c.n2 = containers.size == 0 ? 1.0 :
			w->obj_ar[containers.arr[containers.size - 1]].m->refractive_index;
			aa = x.max_obj;
		}
		aa++;
	}
	free_int(containers.arr);
	return (c);
}

t_comps	prepare_computations(int hit_obj, t_ray r, t_world *w, t_x_t x)
{
	t_comps	c;
	t_vec	normal;

	c.t = x.t[hit_obj].t;
	c.obj = x.t[hit_obj].obj;
	c.point = position(r, c.t);
	c.eyev = neg(r.d);
	if ((*w->obj_ar[c.obj].loc_norm)(w->obj_ar[c.obj].obj, c.point,
	&normal) == 0)
		write(1, "normal error", 12);
	else
		c.normalv = normal;
	if (dot(c.normalv, c.eyev) < 0)
	{
		c.inside = 1;
		c.normalv = neg(c.normalv);
	}
	else
		c.inside = 0;
	c.over_point = add(c.point, mult(c.normalv, EPSILON));
	c.reflectv = reflect(r.d, c.normalv);
	c.under_point = sub(c.point, mult(c.normalv, EPSILON));
	c = comps_n_calculate(w, hit_obj, x, c);
	return (c);
}

t_color	shade_hit(t_world w, t_comps c, int remaining, t_material *m)
{
	t_color	surface;
	t_color	reflected;
	t_color	refracted;
	double	reflectance;

	surface = color(0, 0, 0);
	if (w.light_count == -1)
		surface = mult_col(m->color, m->ambient);
	while (w.light_count >= 0)
	{
		c.shadow = intensity_at(w, c.over_point);
		surface = add_col(surface, lighting(m, w, c));
		w.light_count--;
	}
	reflected = reflected_color(w, c, remaining);
	refracted = refracted_color(w, c, remaining);
	if (m->reflective > 0 && m->transparency > 0)
	{
		reflectance = schlick(c);
		return (add_col(surface, add_col(mult_col(reflected, reflectance),
		mult_col(refracted, (1.0 - reflectance)))));
	}
	else
		return (add_col(refracted, add_col(surface, reflected)));
}

t_color	color_at(t_world *w, t_ray r, int remaining)
{
	t_x_t	x;
	int		hit_obj;
	t_color	col;
	t_comps	comps;

	x.t = alloc_tto(w->ar_count);
	hit_obj = 0;
	intersect_world(w, r, &x);
	hit_obj = hit(x);
	if (hit_obj != -1)
	{
		w->light_count = w->light_obj - 1;
		if (w->effective_render == 0)
		{
			comps = prepare_computations(hit_obj, r, w, x);
			col = shade_hit(*w, comps, remaining, w->obj_ar[comps.obj].m);
		}
		else
			col = effective_shade_hit(*w, w->obj_ar[x.t[hit_obj].obj].m);
	}
	else
		col = color(0, 0, 0);
	free_tto(x.t);
	return (col);
}
