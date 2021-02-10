/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_shape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:42:43 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/05 18:42:51 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	m;

	m = identity_matrix();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	m;

	m = matrix_nul();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_x(double r)
{
	t_matrix	m;

	m = matrix_nul();
	m.m[0][0] = 1;
	m.m[1][1] = cos(r);
	m.m[1][2] = -1 * sin(r);
	m.m[2][1] = sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_y(double r)
{
	t_matrix	m;

	m = matrix_nul();
	m.m[0][0] = cos(r);
	m.m[0][2] = sin(r);
	m.m[1][1] = 1;
	m.m[2][0] = -1 * sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_z(double r)
{
	t_matrix	m;

	m = matrix_nul();
	m.m[0][0] = cos(r);
	m.m[0][1] = -1 * sin(r);
	m.m[1][0] = sin(r);
	m.m[1][1] = cos(r);
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}
