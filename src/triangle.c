/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:01:23 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 19:26:25 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	set_trian(t_vec p1, t_vec p2, t_vec p3, t_trian	*t)
{
	t->p1 = p1;
	t->p2 = p2;
	t->p3 = p3;
	t->e1 = sub(p2, p1);
	t->e2 = sub(p3, p1);
	t->norm = normalize(cross(t->e2, t->e1));
	//t->m = default_material();
	t->transform = identity_matrix();
}

int		normal_at_trian(void *v_s, t_vec world_point, t_vec *n)
{
	t_trian *s;
	t_vec   object_point;
	t_vec   object_normal;
	t_vec	world_normal;

	s = (t_trian*)v_s;
	object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
	object_normal = s->norm;
	world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}

void	intersect_trian(void *v_s, t_ray r, t_x_t *x, int obj_n)
{
	t_ray	ray2;
	t_trian *s;
	t_vec	dir_cross_e2;
	double	det;
	double	f;
	t_vec	p1_to_origin;
	double	u;
	t_vec	origin_cross_e1;
	double	v;


	s = (t_trian*)v_s;
	ray2 = transform(r, matrix_inverse(s->transform));
	dir_cross_e2 = cross(ray2.d, s->e2);
	det = dot(s->e1, dir_cross_e2);
	if (fabs(det) < EPSILON)
		return ;
		//return (x);
	f = 1.0 / det;
	p1_to_origin = sub(ray2.o, s->p1);
	u = f * dot(p1_to_origin, dir_cross_e2);
	if (u < 0 || u > 1)
		return ;
		//return (x);
	origin_cross_e1 = cross(p1_to_origin, s->e1);
	v = f * dot(ray2.d, origin_cross_e1);
	if (v < 0 || (u + v) > 1)
		return ;
		//return (x);
	x->t[x->max_obj].t = f * dot(s->e2, origin_cross_e1);
	x->t[x->max_obj].obj = obj_n;
	x->t[x->max_obj].count = 2;
	x->max_obj += 1;
	//return (x);
}
