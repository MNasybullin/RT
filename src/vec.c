/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:13:49 by aannara           #+#    #+#             */
/*   Updated: 2020/09/21 15:01:31 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"
/*
** d = 0.0 - vector
** d = 1.0 - point
*/
t_vec	set_v_p(double a, double b, double c, double d)
{
	t_vec	t;

	t.c[0] = a;
	t.c[1] = b;
	t.c[2] = c;
	t.c[3] = d;
	return (t);
}

int	check_eps(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
