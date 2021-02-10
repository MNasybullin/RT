/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:54:55 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 16:55:17 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix	matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	m;
	int			r;

	r = 0;
	while (r < 4)
	{
		m.m[r][0] = a.m[r][0] * b.m[0][0] + a.m[r][1] * b.m[1][0]
		+ a.m[r][2] * b.m[2][0] + a.m[r][3] * b.m[3][0];
		m.m[r][1] = a.m[r][0] * b.m[0][1] + a.m[r][1] * b.m[1][1]
		+ a.m[r][2] * b.m[2][1] + a.m[r][3] * b.m[3][1];
		m.m[r][2] = a.m[r][0] * b.m[0][2] + a.m[r][1] * b.m[1][2]
		+ a.m[r][2] * b.m[2][2] + a.m[r][3] * b.m[3][2];
		m.m[r][3] = a.m[r][0] * b.m[0][3] + a.m[r][1] * b.m[1][3]
		+ a.m[r][2] * b.m[2][3] + a.m[r][3] * b.m[3][3];
		r++;
	}
	return (m);
}

t_vec		matrix_mult_v_p(t_matrix a, t_vec b)
{
	t_vec	m;

	m.c[0] = a.m[0][0] * b.c[0] + a.m[0][1] * b.c[1] + a.m[0][2] *
	b.c[2] + a.m[0][3] * b.c[3];
	m.c[1] = a.m[1][0] * b.c[0] + a.m[1][1] * b.c[1] + a.m[1][2] *
	b.c[2] + a.m[1][3] * b.c[3];
	m.c[2] = a.m[2][0] * b.c[0] + a.m[2][1] * b.c[1] + a.m[2][2] *
	b.c[2] + a.m[2][3] * b.c[3];
	m.c[3] = a.m[3][0] * b.c[0] + a.m[3][1] * b.c[1] + a.m[3][2] *
	b.c[2] + a.m[3][3] * b.c[3];
	return (m);
}

t_matrix	matrix_identity(t_matrix a)
{
	t_matrix	m;
	t_matrix	b;
	int			r;

	b = identity_matrix();
	r = 0;
	while (r < 4)
	{
		m.m[r][0] = a.m[r][0] * b.m[0][0] + a.m[r][1] * b.m[1][0] +
		a.m[r][2] * b.m[2][0] + a.m[r][3] * b.m[3][0];
		m.m[r][1] = a.m[r][0] * b.m[0][1] + a.m[r][1] * b.m[1][1] +
		a.m[r][2] * b.m[2][1] + a.m[r][3] * b.m[3][1];
		m.m[r][2] = a.m[r][0] * b.m[0][2] + a.m[r][1] * b.m[1][2] +
		a.m[r][2] * b.m[2][2] + a.m[r][3] * b.m[3][2];
		m.m[r][3] = a.m[r][0] * b.m[0][3] + a.m[r][1] * b.m[1][3] +
		a.m[r][2] * b.m[2][3] + a.m[r][3] * b.m[3][3];
		r++;
	}
	return (m);
}

t_vec		matrix_identity_v_p(t_vec a)
{
	t_vec		m;
	t_matrix	b;
	int			r;

	b = identity_matrix();
	r = 0;
	while (r < 4)
	{
		m.c[r] = a.c[r] * b.m[0][0] + a.c[r] * b.m[1][0] + a.c[r] *
		b.m[2][0] + a.c[r] * b.m[3][0];
		m.c[r] = a.c[r] * b.m[0][1] + a.c[r] * b.m[1][1] + a.c[r] *
		b.m[2][1] + a.c[r] * b.m[3][1];
		m.c[r] = a.c[r] * b.m[0][2] + a.c[r] * b.m[1][2] + a.c[r] *
		b.m[2][2] + a.c[r] * b.m[3][2];
		m.c[r] = a.c[r] * b.m[0][3] + a.c[r] * b.m[1][3] + a.c[r] *
		b.m[2][3] + a.c[r] * b.m[3][3];
		r++;
	}
	return (m);
}

t_matrix	matrix_transposing(t_matrix a)
{
	t_matrix	b;

	b.m[0][0] = a.m[0][0];
	b.m[1][0] = a.m[0][1];
	b.m[2][0] = a.m[0][2];
	b.m[3][0] = a.m[0][3];
	b.m[0][1] = a.m[1][0];
	b.m[1][1] = a.m[1][1];
	b.m[2][1] = a.m[1][2];
	b.m[3][1] = a.m[1][3];
	b.m[0][2] = a.m[2][0];
	b.m[1][2] = a.m[2][1];
	b.m[2][2] = a.m[2][2];
	b.m[3][2] = a.m[2][3];
	b.m[0][3] = a.m[3][0];
	b.m[1][3] = a.m[3][1];
	b.m[2][3] = a.m[3][2];
	b.m[3][3] = a.m[3][3];
	return (b);
}
