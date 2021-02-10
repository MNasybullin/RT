/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 17:56:23 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			uv_patter_at_texture(SDL_Surface *texture, double u, double v)
{
	double	x;
	double	y;

	v = 1 - v;
	x = u * (texture->w - 1);
	y = v * (texture->h - 1);
	return (get_color_tex(texture, (int)x, (int)y));
}

void			uv_checkers(t_uv_check c, t_pattern *p)
{
	p->a = c.color_a;
	p->b = c.color_b;
	p->height = c.height;
	p->width = c.width;
}

/*
** Identifying the face of a cube from a point
** return 0 - right; 1 - left; 2 - up; 3 - down; 4 - front; 5 - back;
*/

int				face_from_point(t_vec point)
{
	double coord;

	coord = max(fabs(point.c[0]), fabs(point.c[1]), fabs(point.c[2]));
	if (coord == point.c[0])
		return (0);
	if (coord == -point.c[0])
		return (1);
	if (coord == point.c[1])
		return (2);
	if (coord == -point.c[1])
		return (3);
	if (coord == point.c[2])
		return (4);
	return (5);
}

/*
t_pattern		uv_align_check(t_color main, t_color ul, t_color ur, t_color bl, t_color br, int face)
{
	t_pattern	p;

	p.main[face] = main;
	p.ul[face] = ul;
	p.ur[face] = ur;
	p.bl[face] = bl;
	p.br[face] = br;
	return (p);
}
*/

t_color			uv_patter_at(t_pattern checkers, double u, double v)
{
	double	u2;
	double	v2;

	u2 = floor(u * (double)checkers.width);
	v2 = floor(v * (double)checkers.height);
	if (realmod((u2 + v2), 2) == 0)
		return (checkers.a);
	else
		return (checkers.b);
}

t_color			pattern_at(t_material m, t_vec point)
{
	t_vec	uv;
	t_color	color;

	uv = (m.texturemap.uv_map)(point);
	if (m.tex == 1)
		color = uv_patter_at_texture(m.texture, uv.c[0], uv.c[1]);
	else
		color = uv_patter_at(m.texturemap.uv_pattern, uv.c[0], uv.c[1]);
	return (color);
}
