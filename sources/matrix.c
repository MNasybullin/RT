/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:50:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 16:55:14 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		matrix_determinant_2(t_matrix m)
{
	return ((m.m[0][0] * m.m[1][1]) - (m.m[0][1] * m.m[1][0]));
}

t_matrix	matrix_submatrix(t_matrix m, int a, int b, int size)
{
	t_matrix	v;
	int			i;
	int			j;
	int			r;
	int			c;

	i = 0;
	r = 0;
	while (i < size)
	{
		j = 0;
		c = 0;
		if (i != a)
		{
			while (j < size)
			{
				if (j != b)
					v.m[r][c++] = m.m[i][j];
				j++;
			}
			r++;
		}
		i++;
	}
	return (v);
}

t_matrix	matrix_inverse(t_matrix m)
{
	t_matrix	m2;
	double		determinant_4;

	determinant_4 = matrix_determinant_4(m);
	m2.m[0][0] = matrix_cofactor(m, 0, 0, 4) / determinant_4;
	m2.m[1][0] = matrix_cofactor(m, 0, 1, 4) / determinant_4;
	m2.m[2][0] = matrix_cofactor(m, 0, 2, 4) / determinant_4;
	m2.m[3][0] = matrix_cofactor(m, 0, 3, 4) / determinant_4;
	m2.m[0][1] = matrix_cofactor(m, 1, 0, 4) / determinant_4;
	m2.m[1][1] = matrix_cofactor(m, 1, 1, 4) / determinant_4;
	m2.m[2][1] = matrix_cofactor(m, 1, 2, 4) / determinant_4;
	m2.m[3][1] = matrix_cofactor(m, 1, 3, 4) / determinant_4;
	m2.m[0][2] = matrix_cofactor(m, 2, 0, 4) / determinant_4;
	m2.m[1][2] = matrix_cofactor(m, 2, 1, 4) / determinant_4;
	m2.m[2][2] = matrix_cofactor(m, 2, 2, 4) / determinant_4;
	m2.m[3][2] = matrix_cofactor(m, 2, 3, 4) / determinant_4;
	m2.m[0][3] = matrix_cofactor(m, 3, 0, 4) / determinant_4;
	m2.m[1][3] = matrix_cofactor(m, 3, 1, 4) / determinant_4;
	m2.m[2][3] = matrix_cofactor(m, 3, 2, 4) / determinant_4;
	m2.m[3][3] = matrix_cofactor(m, 3, 3, 4) / determinant_4;
	return (m2);
}

t_matrix	matrix_nul(void)
{
	t_matrix	m;

	m.m[0][0] = 0;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = 0;
	m.m[1][2] = 0;
	m.m[1][3] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 0;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 0;
	return (m);
}

t_matrix	identity_matrix(void)
{
	t_matrix	b;

	b = matrix_nul();
	b.m[0][0] = 1;
	b.m[1][1] = 1;
	b.m[2][2] = 1;
	b.m[3][3] = 1;
	return (b);
}
