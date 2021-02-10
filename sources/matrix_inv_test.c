/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inv_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:52:27 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 16:53:01 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		matrix_minor(t_matrix m, int a, int b, int size)
{
	m = matrix_submatrix(m, a, b, size);
	return (size == 4 ? matrix_determinant_3(m) : matrix_determinant_2(m));
}

double		matrix_cofactor(t_matrix m, int a, int b, int size)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			c = i + j;
			if (c == 1 || c == 3 || c == 5 || c == 7)
				m.m[i][j] = -m.m[i][j];
			j++;
		}
		i++;
	}
	return (matrix_minor(m, a, b, size));
}

double		matrix_determinant_3(t_matrix m)
{
	return ((m.m[0][0] * matrix_cofactor(m, 0, 0, 3))
	+ (m.m[0][1] * matrix_cofactor(m, 0, 1, 3))
	+ (m.m[0][2] * matrix_cofactor(m, 0, 2, 3)));
}

double		matrix_determinant_4(t_matrix m)
{
	return ((m.m[0][0] * matrix_cofactor(m, 0, 0, 4))
	+ (m.m[0][1] * matrix_cofactor(m, 0, 1, 4))
	+ (m.m[0][2] * matrix_cofactor(m, 0, 2, 4))
	+ (m.m[0][3] * matrix_cofactor(m, 0, 3, 4)));
}

int			matrix_inverse_test(t_matrix m)
{
	if (matrix_determinant_4(m) == 0)
		return (0);
	return (1);
}
