/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:18:26 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/10 21:30:56 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			realmod(double x, double p)
{
	if (x < 0)
		return (fmod((fmod(x, p) + p), p));
	else
		return (fmod(x, p));
}

t_color			stripe_at(t_material m, t_vec point)
{
	if (realmod(floor(point.c[0]), 2) == 0)
		return (m.p.a);
	else
		return (m.p.b);
}

t_color			gradient_at(t_material m, t_vec point)
{
	t_color	distance;
	double	fraction;

	distance = sub_col(m.p.b, m.p.a);
	fraction = point.c[0] - floor(point.c[0]);
	return (add_col(m.p.a, mult_col(distance, fraction)));
}

t_color			ring_at(t_material m, t_vec point)
{
	if (realmod(floor(sqrt((point.c[0] * point.c[0]) +
	(point.c[2] * point.c[2]))), 2) == 0)
		return (m.p.a);
	else
		return (m.p.b);
}

t_color			checker_at(t_material m, t_vec point)
{
	if ((realmod(floor(point.c[0]) + floor(point.c[1]) +
	floor(point.c[2]), 2)) == 0)
		return (m.p.a);
	else
		return (m.p.b);
}
