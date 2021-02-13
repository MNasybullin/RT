/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schlick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 23:32:25 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/13 18:31:27 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	schlick(t_comps c)
{
	double	cos;
	double	n;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos = dot(c.eyev, c.normalv);
	if (c.n1 > c.n2)
	{
		n = c.n1 / c.n2;
		sin2_t = (n * n) * (1.0 - (cos * cos));
		if (sin2_t > 1.0)
		{
			return (1.0);
		}
		cos_t = SDL_sqrt(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = ((c.n1 - c.n2) / (c.n1 + c.n2)) * ((c.n1 - c.n2) / (c.n1 + c.n2));
	return (r0 + (1.0 - r0) * pow((1.0 - cos), 5));
}
