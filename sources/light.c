/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:31:01 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/06 18:25:33 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		point_on_light(t_light *l, int u, int v)
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

void		lighting_dot_norm(t_world w, t_lighting *l, t_comps c,
t_material *m)
{
	if (l->light_dot_normal < 0)
	{
		l->diffuse = color(0, 0, 0);
		l->specular = color(0, 0, 0);
	}
	else
	{
		l->diffuse = mult_col(mult_col(mult_col(l->effective_color, m->diffuse),
		l->light_dot_normal), c.shadow);
		l->reflect_v = reflect(neg(l->light_v), c.normalv);
		l->reflect_dot_eye = dot(l->reflect_v, c.eyev);
		if (l->reflect_dot_eye <= 0)
			l->specular = color(0, 0, 0);
		else
		{
			l->factor = powf(l->reflect_dot_eye, m->shininess);
			l->specular = mult_col(mult_col(mult_col(
				w.light[w.light_count].intensity, m->specular),
				l->factor), c.shadow);
		}
	}
}

void		lighting_shadow(t_world w, t_lighting *l, t_comps c, t_material *m)
{
	int	usteps;
	int	vsteps;
	int	u;
	int	v;

	usteps = w.light[w.light_count].usteps;
	vsteps = w.light[w.light_count].vsteps;
	v = 0;
	while (v < vsteps)
	{
		u = 0;
		while (u < usteps)
		{
			l->light_v = normalize(sub(point_on_light(&w.light[w.light_count],
			u, v), c.over_point));
			l->light_dot_normal = dot(l->light_v, c.normalv);
			lighting_dot_norm(w, l, c, m);
			l->sum = add_col(add_col(l->sum, l->diffuse), l->specular);
			u++;
		}
		v++;
	}
}

t_vec		world_point_to_pattern_point(t_pattern p, t_matrix transform,
t_vec world_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;

	obj_point = matrix_mult_v_p(transform, world_point);
	pattern_point = matrix_mult_v_p(p.transform, obj_point);
	return (pattern_point);
}

t_color		lighting(t_material *m, t_world w, t_comps c)
{
	t_lighting	l;
	t_color		m_color;

	m_color = m->color;
	if (m->pattern == 1)
	{
		l.point = world_point_to_pattern_point(m->p, *w.obj_ar[c.obj].transform,
		c.over_point);
		m_color = (*m->pattern_at)(*m, l.point);
	}
	l.effective_color = hadamard_prod(m_color,
	w.light[w.light_count].intensity);
	l.ambient = mult_col(l.effective_color, m->ambient);
	if (c.shadow > 0.0)
	{
		l.sum = color(0, 0, 0);
		lighting_shadow(w, &l, c, m);
		return (add_col(mult_col(divide_col(l.sum,
		w.light[w.light_count].samples), c.shadow), l.ambient));
	}
	else
		return (l.ambient);
}
