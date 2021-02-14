/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:27:10 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 14:23:01 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light		area_light(t_vec corner, t_vec full_uvec, int usteps, t_vec full_vvec, int vsteps, t_color color)
{
	t_light	l;

	l.intensity = color;
	l.corner = corner;
	l.uvec = divi(full_uvec, usteps);
	l.usteps = usteps;
	l.vvec = divi(full_vvec, vsteps);
	l.vsteps = vsteps;
	l.samples = usteps * vsteps;
	return (l);
}

t_light		point_light(t_color color, t_vec pos)
{
	t_light	l;
	t_vec	full_uvec;
	t_vec	full_vvec;

	full_uvec = set_v_p(1, 0, 0, 0);
	full_vvec = set_v_p(0, 1, 0, 0);
	l.intensity = color;
	l.usteps = 1;
	l.vsteps = 1;
	l.uvec = divi(full_uvec, 1);
	l.vvec = divi(full_vvec, 1);
	l.samples = 1;
	l.corner = pos;
	return (l);
}

int			hit(t_x_t x)
{
	int	i;
	int	a;

	i = 0;
	a = -1;
	while (i < x.max_obj)
	{
		if (x.t[i].count > 0 && x.t[i].t >= 0)
		{
			if (a == -1)
				a = i;
			if (x.t[i].t < x.t[a].t)
				a = i;
		}
		i++;
	}
	return (a);
}

double			is_shadow(t_world w, t_vec light_pos, t_vec p)
{
	t_vec	v;
	t_vec	direction;
	double	distance;
	t_x_t	x;
	int		hit_obj;
	double	shadow_intens;

	shadow_intens = 0;
	x.t = alloc_tto(w.ar_count);
	v = sub(light_pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	intersect_world(&w, set_ray(p, direction), &x);
	hit_obj = hit(x);
	if (hit_obj != -1 && x.t[hit_obj].t < distance)
	{
		if (w.obj_ar[x.t[hit_obj].obj].m->shadow != 0)
		{
			shadow_intens = w.obj_ar[x.t[hit_obj].obj].m->transparency == 0 ? -1 : w.obj_ar[x.t[hit_obj].obj].m->transparency;
			free_tto(x.t);
			return (shadow_intens);
		}
	}
	free_tto(x.t);
	return (0.0);
}

double		intensity_at(t_world w, t_vec p)
{
	double	total;
	int		u;
	int		v;
	t_vec	light_position;
	double	is_shad;

	v = 0;
	total = 0.0;
	while (v < w.light[w.light_count].vsteps)
	{
		u = 0;
		while (u < w.light[w.light_count].usteps)
		{
			light_position = point_on_light(&w.light[w.light_count], u, v);
			is_shad = is_shadow(w, light_position, p);
			if (is_shad == 0.0)
				total += 1.0;
			else if (is_shad != -1)
				total += is_shad;
			u++;
		}
		v++;
	}
	return (total / w.light[w.light_count].samples);
}
