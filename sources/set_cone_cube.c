/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cone_cube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:43:41 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/13 18:36:07 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone	set_cone(void)
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

int		normal_at_cone(void *v_s, t_vec world_point, t_vec *n)
{
	t_cone	*s;
	t_vec	obj_p;
	t_vec	obj_n;
	t_vec	world_normal;
	double	dist;

	s = (t_cone*)v_s;
	obj_p = matrix_mult_v_p(s->transform, world_point);
	dist = (obj_p.c[0] * obj_p.c[0]) + (obj_p.c[2] * obj_p.c[2]);
	if (dist < 1 && obj_p.c[1] >= s->max - EPSILON)
		obj_n = set_v_p(0, 1, 0, 0);
	else if (dist < 1 && obj_p.c[1] <= s->min + EPSILON)
		obj_n = set_v_p(0, -1, 0, 0);
	else
	{
		dist = SDL_sqrt(dist);
		if (obj_p.c[1] > 0)
			dist = -dist;
		obj_n = set_v_p(obj_p.c[0], dist, obj_p.c[2], 0);
	}
	world_normal = matrix_mult_v_p(matrix_transposing(s->transform), obj_n);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}

t_cube	set_cube(void)
{
	t_cube	c;

	c.c = set_v_p(0, 0, 0, 1);
	c.transform = identity_matrix();
	c.m = default_material();
	return (c);
}

int		normal_at_cube(void *v_s, t_vec world_point, t_vec *n)
{
	t_cube	*s;
	t_vec	object_point;
	t_vec	object_normal;
	t_vec	world_normal;
	double	maxc;

	s = (t_cube*)v_s;
	object_point = matrix_mult_v_p(s->transform, world_point);
	maxc = max(SDL_fabs(object_point.c[0]), SDL_fabs(object_point.c[1]),
	SDL_fabs(object_point.c[2]));
	if (maxc == SDL_fabs(object_point.c[0]))
		object_normal = set_v_p(object_point.c[0], 0, 0, 0);
	else if (maxc == SDL_fabs(object_point.c[1]))
		object_normal = set_v_p(0, object_point.c[1], 0, 0);
	else
		object_normal = set_v_p(0, 0, object_point.c[2], 0);
	world_normal = matrix_mult_v_p(matrix_transposing(s->transform),
	object_normal);
	world_normal.c[3] = 0;
	*n = normalize(world_normal);
	return (1);
}
