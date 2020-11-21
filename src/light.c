/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:31:01 by sdiego            #+#    #+#             */
/*   Updated: 2020/11/21 19:09:56 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec	point_on_light(t_light *l, int u, int v)
{
	double	a;
	double	b;
	t_vec	umult;
	t_vec	vmult;
	t_vec	uv;

	if (l->samples == 1)
	{
		a = u;
		b = v;
	}
	else
	{
		a = u + drand48();
		b = v + drand48();
	}
	umult = mult(l->uvec, a);
	vmult = mult(l->vvec, b);
	uv = add(umult, vmult);
	return (add(l->corner, uv));
}

t_light	area_light(t_vec corner, t_vec full_uvec, int usteps, t_vec full_vvec, int vsteps, t_color color)
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

t_light	point_light(t_color color, t_vec pos)
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

t_material	default_material(void)
{
	t_material	m;

	m.color = color(0.5, 0.5, 0.5);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.reflective = 0;
	m.pattern = 0;
	m.refractive_index = 1;
	m.transparency = 0;
	m.shadow = 1;
	return (m);
}

double	intensity_at(t_world w, t_vec p)
{
	double	total;
	int		u;
	int		v;
	t_vec	light_position;

	v = 0;
	total = 0.0;
	while (v < w.light[w.light_count].vsteps)
	{
		u = 0;
		while (u < w.light[w.light_count].usteps)
		{
			light_position = point_on_light(&w.light[w.light_count], u, v);
			if (is_shadow(w, light_position, p) == 0)
				total += 1.0;
			u++;
		}
		v++;
	}
	return (total / w.light[w.light_count].samples);
}

int	is_shadow(t_world w, t_vec light_pos, t_vec p)
{
	t_vec	v;
	t_vec	direction;
	double	distance;
	t_x_t	x;
	int		hit_obj;

	v = sub(light_pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	intersect_world(&w, set_ray(p, direction), &x);
	hit_obj = hit(x);
	if (hit_obj != -1 && x.t[hit_obj].t < distance)
	{
		if (w.obj_ar[x.t[hit_obj].obj].m->shadow != 0)
			return (1);
		return (0);
	}
	else
		return (0);
}

t_color	lighting(t_material *m, t_world w, t_comps c)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	double	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	double	reflect_dot_eye;
	double	factor;

	if (m->pattern == 1)
	{
		t_vec point = world_point_to_pattern_point(m->p, *w.obj_ar[c.obj].transform, c.over_point);
		m->color = (*m->pattern_at)(*m, point);
	}
	effective_color = hadamard_prod(m->color, w.light[w.light_count].intensity);
	ambient = mult_col(effective_color, m->ambient);
	//light_v = normalize(sub(w.light[w.light_count].pos, c.over_point));
	//light_dot_normal = dot(light_v, c.normalv);
	if (c.shadow > 0.0) //
	{
		t_color sum = color(0, 0, 0);
		int	usteps = w.light[w.light_count].usteps;
		int	vsteps = w.light[w.light_count].vsteps;
		int u = 0;
		int v = 0;
		while (v < vsteps)
		{
			u = 0;
			while (u < usteps)
			{
				t_vec light_position = point_on_light(&w.light[w.light_count], u, v);

				light_v = normalize(sub(light_position, c.over_point));
				light_dot_normal = dot(light_v, c.normalv);
				if (light_dot_normal < 0)
				{
					diffuse = color(0, 0, 0);
					specular = color(0, 0, 0);
				}
				else
				{
					diffuse = mult_col(mult_col(mult_col(effective_color, m->diffuse), light_dot_normal), c.shadow);

					reflect_v = reflect(neg(light_v), c.normalv);
					reflect_dot_eye = dot(reflect_v, c.eyev);
					if (reflect_dot_eye <= 0)
						specular = color(0, 0, 0);
					else
					{
						factor = powf(reflect_dot_eye, m->shininess);
						specular = mult_col(mult_col(mult_col(w.light[w.light_count].intensity, m->specular), factor), c.shadow);
					}
				}
				sum = add_col(add_col(sum, diffuse), specular);
				u++;
			}
			v++;
		}
		return (add_col(mult_col(divide_col(sum, w.light[w.light_count].samples), c.shadow), ambient));
	}
	else
		return (ambient);
}
