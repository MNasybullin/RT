/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:49:00 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/06 18:18:58 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int			check_transform_matrix(t_matrix *transform,
t_matrix *pattern_transform, int pattern)
{
	if (matrix_inverse_test(*transform) != 1)
	{
		write(1, "matrix_inverse_test error in shape transform\n", 45);
		return (EXIT_FAILURE);
	}
	*transform = matrix_inverse(*transform);
	if (pattern == 1)
	{
		if (matrix_inverse_test(*pattern_transform) != 1)
		{
			write(1, "matrix_inverse_test error in shape pattern\n", 43);
			return (EXIT_FAILURE);
		}
		*pattern_transform = matrix_inverse(*pattern_transform);
	}
	return (EXIT_SUCCESS);
}

t_ray		transform(t_ray r, t_matrix m)
{
	t_ray	r2;

	r2.o = matrix_mult_v_p(m, r.o);
	r2.d = matrix_mult_v_p(m, r.d);
	return (r2);
}

t_matrix	set_transform(t_matrix s, t_matrix m)
{
	s = matrix_mult(m, s);
	return (s);
}

t_matrix	view_transform(t_vec from, t_vec to, t_vec up)
{
	t_vec		forward;
	t_vec		upn;
	t_vec		left;
	t_vec		true_up;
	t_matrix	orientation;

	forward = normalize(sub(to, from));
	upn = normalize(up);
	left = cross(forward, upn);
	true_up = cross(left, forward);
	orientation = matrix_nul();
	orientation.m[0][0] = left.c[0];
	orientation.m[0][1] = left.c[1];
	orientation.m[0][2] = left.c[2];
	orientation.m[1][0] = true_up.c[0];
	orientation.m[1][1] = true_up.c[1];
	orientation.m[1][2] = true_up.c[2];
	orientation.m[2][0] = -forward.c[0];
	orientation.m[2][1] = -forward.c[1];
	orientation.m[2][2] = -forward.c[2];
	orientation.m[3][3] = 1;
	return (matrix_mult(orientation,
	translation(-from.c[0], -from.c[1], -from.c[2])));
}

/*
t_matrix	default_view_transf(void)
{
	t_vec		from;
	t_vec		to;
	t_vec		up;
	t_matrix	t;

	from = set_v_p(0, 0, 0, 1);
	to = set_v_p(0, 0, -1, 1);
	up = set_v_p(0, 1, 0, 0);
	t = view_transform(from, to, up);
	return (t);
}
*/
