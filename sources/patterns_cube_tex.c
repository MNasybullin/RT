/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_cube_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:02:03 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 17:02:23 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			cube_uv_back(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(1 - point.c[0], 2) / 2;
	v = realmod(point.c[1] + 1, 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			cube_uv_left(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(point.c[2] + 1, 2) / 2;
	v = realmod(point.c[1] + 1, 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			cube_uv_right(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(1 - point.c[2], 2) / 2;
	v = realmod(point.c[1] + 1, 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			cube_uv_up(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(point.c[0] + 1, 2) / 2;
	v = realmod(1 - point.c[2], 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			cube_uv_down(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(point.c[0] + 1, 2) / 2;
	v = realmod(point.c[2] + 1, 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}
