/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_cube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:59:43 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 17:03:18 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		cube_uv_front(t_vec point)
{
	t_vec	uv;
	double	u;
	double	v;

	u = realmod(point.c[0] + 1, 2) / 2;
	v = realmod(point.c[1] + 1, 2) / 2;
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_color		uv_pattern_at_cube(t_pattern pattern, double u, double v, int face)
{
	if (v > 0.8)
	{
		if (u < 0.2)
			return (pattern.ul[face]);
		if (u > 0.8)
			return (pattern.ur[face]);
	}
	else if (v < 0.2)
	{
		if (u < 0.2)
			return (pattern.bl[face]);
		if (u > 0.8)
			return (pattern.br[face]);
	}
	return (pattern.main[face]);
}

t_color		pattern_at_cube_texture(t_material m, t_vec point)
{
	int		face;
	t_vec	uv;

	face = face_from_point(point);
	if (face == 0)
		uv = cube_uv_right(point);
	else if (face == 1)
		uv = cube_uv_left(point);
	else if (face == 2)
		uv = cube_uv_up(point);
	else if (face == 3)
		uv = cube_uv_down(point);
	else if (face == 4)
		uv = cube_uv_front(point);
	else
		uv = cube_uv_back(point);
	return (uv_patter_at_texture(m.p.cube_texture[face], uv.c[0], uv.c[1]));
}

t_color		pattern_at_cube(t_material m, t_vec point)
{
	int		face;
	t_vec	uv;

	face = face_from_point(point);
	if (face == 0)
		uv = cube_uv_right(point);
	else if (face == 1)
		uv = cube_uv_left(point);
	else if (face == 2)
		uv = cube_uv_up(point);
	else if (face == 3)
		uv = cube_uv_down(point);
	else if (face == 4)
		uv = cube_uv_front(point);
	else
		uv = cube_uv_back(point);
	return (uv_pattern_at_cube(m.p, uv.c[0], uv.c[1], face));
}
