/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:58:22 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/08 18:13:55 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec			cylindrical_map(t_vec p)
{
	double	theta;
	double	raw_u;
	double	u;
	double	v;
	t_vec	uv;

	theta = atan2(p.c[0], p.c[2]);
	raw_u = theta / (2 * M_PI);
	u = 1 - (raw_u + 0.5);
	v = realmod(p.c[1], 1);
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			planar_map(t_vec p)
{
	double	u;
	double	v;
	t_vec	uv;

	u = realmod(p.c[0], 1);
	v = realmod(p.c[2], 1);
	uv = set_v_p(u, v, 0, 0);
	return (uv);
}

t_vec			spherical_map(t_vec p)
{
	double	theta;
	t_vec	vec;
	double	phi;
	double	u;
	double	v;

	theta = atan2(p.c[0], p.c[2]);
	vec = set_v_p(p.c[0], p.c[1], p.c[2], 0);
	phi = acos(p.c[1] / magnitude(vec));
	u = 1 - ((theta / (2 * M_PI)) + 0.5);
	v = 1 - phi / M_PI;
	return (set_v_p(u, v, 0, 0));
}

t_texturemap	texture_map(t_pattern checkers, t_vec (*spherical_map)(t_vec))
{
	t_texturemap	pattern;

	pattern.uv_map = spherical_map;
	pattern.uv_pattern = checkers;
	return (pattern);
}
