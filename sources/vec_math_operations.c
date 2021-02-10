/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:37:35 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/05 18:37:39 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	add(t_vec a1, t_vec a2)
{
	a1.c[0] += a2.c[0];
	a1.c[1] += a2.c[1];
	a1.c[2] += a2.c[2];
	a1.c[3] += a2.c[3];
	return (a1);
}

t_vec	sub(t_vec a1, t_vec a2)
{
	a1.c[0] -= a2.c[0];
	a1.c[1] -= a2.c[1];
	a1.c[2] -= a2.c[2];
	a1.c[3] -= a2.c[3];
	return (a1);
}

t_vec	neg(t_vec a)
{
	a.c[0] *= -1;
	a.c[1] *= -1;
	a.c[2] *= -1;
	a.c[3] *= -1;
	return (a);
}

t_vec	mult(t_vec a, double b)
{
	a.c[0] *= b;
	a.c[1] *= b;
	a.c[2] *= b;
	a.c[3] *= b;
	return (a);
}

t_vec	divi(t_vec a, double b)
{
	a.c[0] /= b;
	a.c[1] /= b;
	a.c[2] /= b;
	a.c[3] /= b;
	return (a);
}
