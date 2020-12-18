/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:09:18 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/12 15:46:56 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
	m.p.transform = identity_matrix();
	return (m);
}

void		intersect_world(t_world *w, t_ray r, t_x_t *x)
{
	int		i;

	i = 0;
	x->max_obj = 0;
	while (i < w->ar_count)
	{
		(*w->obj_ar[i].loc_intersect)(w->obj_ar[i].obj, r, x, i);
		i++;
	}
}

t_arr		removenull(t_arr arr, int stack_size)
{
	t_arr	res;
	int		aa;
	int		bb;

	res.arr = alloc_int(stack_size);
	res.size = 0;
	aa = 0;
	bb = 0;
	while (aa < arr.size)
	{
		if (arr.arr[aa] != -1)
		{
			res.arr[bb] = arr.arr[aa];
			++bb;
			res.size = bb;
		}
		aa++;
	}
	free_int(arr.arr);
	return (res);
}

t_color		effective_shade_hit(t_world w, t_material *m)
{
	t_color	surface;

	surface = color(0, 0, 0);
	if (w.light_count >= 0)
		return (m->color);
	return (surface);
}
