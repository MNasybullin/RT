/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:38:47 by sdiego            #+#    #+#             */
/*   Updated: 2020/11/21 19:40:59 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec	position(t_ray r, double t)
{
	t_vec	a;
	t_vec	b;

	a = mult(r.d, t);
	b = add(r.o, a);
	return (b);
}

t_ray	set_ray(t_vec or, t_vec di)
{
	t_ray	r;

	r.o = or;
	r.d = di;
	return (r);
}
