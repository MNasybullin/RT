/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:19:19 by aannara           #+#    #+#             */
/*   Updated: 2020/12/12 14:56:10 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	magnitude(t_vec a)
{
	return (sqrt(a.c[0] * a.c[0] + a.c[1] * a.c[1] +
	a.c[2] * a.c[2] + a.c[3] * a.c[3]));
}

t_vec	normalize(t_vec v)
{
	double	mg;

	mg = magnitude(v);
	v.c[0] /= mg;
	v.c[1] /= mg;
	v.c[2] /= mg;
	v.c[3] /= mg;
	return (v);
}

double	dot(t_vec a, t_vec b)
{
	return (a.c[0] * b.c[0] + a.c[1] * b.c[1] + a.c[2] *
	b.c[2] + a.c[3] * b.c[3]);
}

t_vec	cross(t_vec a, t_vec b)
{
	return (set_v_p(a.c[1] * b.c[2] - a.c[2] * b.c[1], a.c[2] *
	b.c[0] - a.c[0] * b.c[2], a.c[0] * b.c[1] - a.c[1] * b.c[0], 0));
}

int		identic_m_4(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (fabs(a.m[i][j] - b.m[i][j]) >= EPSILON)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
