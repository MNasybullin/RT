/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:54:30 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 17:34:30 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_sp	set_sphere()
{
	t_sp	s;

	s.c = set_v_p(0, 0, 0, 1);
	s.r = 1;
	s.transform = identity_matrix();
	s.m = default_material();
	return (s);
}

t_sp	glass_sp(t_sp s)
{
	s.m.transparency = 1;
	s.m.refractive_index = 1.5;
	return (s);
}

void	intersect_sp(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	double	a;
	double	b;
	double	c;
	t_vec	sp_to_ray;
	double	disc;
	t_ray	ray2;
	t_sp	*s;

	s = (t_sp*)v_s;
	ray2 = transform(r, matrix_inverse(s->transform));
	sp_to_ray = sub(ray2.o, s->c);
	a = dot(ray2.d, ray2.d);
	b = 2 * dot(ray2.d, sp_to_ray);
	c = dot(sp_to_ray, sp_to_ray) - 1;
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return ;
		//return (x);
	else
	{
		x->t[x->max_obj].t = ((-b - sqrt(disc)) / (2 * a));
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
		x->t[x->max_obj].t = ((-b + sqrt(disc)) / (2 * a));
		x->t[x->max_obj].obj = obj_n;
		x->t[x->max_obj].count = 2;
		x->max_obj += 1;
		//return (x);
	}
}

int		normal_at_sp(void *v_s, t_vec world_point, t_vec *n)
{
	t_sp	*s;
	t_vec object_point;
	t_vec object_normal;
	t_vec	world_normal;

	s = (t_sp*)v_s;
	object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
	object_normal = sub(object_point, set_v_p(0, 0, 0, 1));
	world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}
