/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/24 20:30:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_pattern uv_checkers(int width, int height, t_color a, t_color b)
{
    t_pattern p;

    p.a = a;
    p.b = b;
    p.height = height;
    p.width = width;
    return (p);
}

t_color uv_patter_at(t_pattern checkers, double u, double v)
{
    double u2;
    double v2;

    u2 = floor(u * checkers.width);
    v2 = floor(v * checkers.height);
    if (fmod((u2 + v2), 2) == 0)
        return(checkers.a);
    else
        return(checkers.b);
}


t_vec   spherical_map(t_vec p)
{
    /*
    ** # compute the azimuthal angle
    ** # -π < theta <= π
    ** # angle increases clockwise as viewed from above,
    ** # which is opposite of what we want, but we'll fix it later.
    */
   double theta = atan2(p.c[0], p.c[2]);

   /*
   ** # vec is the vector pointing from the sphere's origin (the world origin)
   ** # to the point, which will also happen to be exactly equal to the sphere's
   ** # radius.
   */
    t_vec vec = set_v_p(p.c[0], p.c[1], p.c[2], 0);
    double radius = magnitude(vec);

    /*
    # compute the polar angle
    # 0 <= phi <= π
    */
    double phi = acos(p.c[1] / radius);

    /*
    ** # -0.5 < raw_u <= 0.5
    */
    double raw_u = theta / (2 * M_PI);

    /*
    **  # 0 <= u < 1
        # here's also where we fix the direction of u. Subtract it from 1,
        # so that it increases counterclockwise as viewed from above.
    */
    double u = 1 - (raw_u + 0.5);

    /*
    # we want v to be 0 at the south pole of the sphere,
     # and 1 at the north pole, so we have to "flip it over"
    # by subtracting it from 1.
    */
    double v = 1 - phi / M_PI;

    t_vec uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_texturemap texture_map(t_pattern checkers, t_vec (*spherical_map)(t_vec))
{
    t_texturemap pattern;
    pattern.uv_map = spherical_map;
    pattern.uv_pattern = checkers;
    return (pattern);
}

/*
** texture_map можно совместить с pattern at и избавиться от стуркуты texturemap !!!!!!!!!
*/
t_color pattern_at(t_texturemap pattern, t_vec point)
{
    t_vec uv;
    t_color color;

    uv = (*pattern.uv_map)(point);
    color = uv_patter_at(pattern.uv_pattern, uv.c[0], uv.c[1]);
    return (color);
}




t_color	stripe_pattern(t_pattern p, t_matrix transform, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;

	if (matrix_inverse_test(transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(transform), wolrd_point);
	else
		printf("matrix s stripe error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe error\n");
	return(stripe_at(p, pattern_point));
}

t_color	gradient_pattern(t_pattern p, t_matrix transform, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;

	if (matrix_inverse_test(transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(transform), wolrd_point);
	else
		printf("matrix s stripe error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe error\n");
	return(gradient_at(p, pattern_point));
}

t_color	ring_pattern(t_pattern p, t_matrix transform, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;

	if (matrix_inverse_test(transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(transform), wolrd_point);
	else
		printf("matrix s stripe error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe error\n");
	return(ring_at(p, pattern_point));
}

t_color	checker_pattern(t_pattern p, t_matrix transform, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;

	if (matrix_inverse_test(transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(transform), wolrd_point);
	else
		printf("matrix s stripe error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe error\n");
	return(checker_at(p, pattern_point));
}

void   stripe_pattern_shape(t_color a, t_color b, t_material *m)
{
    m->p.a = a;
    m->p.b = b;
    m->p.transform = identity_matrix();
    m->pattern = 1;
    m->pattern_at = &stripe_pattern;
}

void   gradient_pattern_shape(t_color a, t_color b, t_material *m)
{
    m->p.a = a;
    m->p.b = b;
    m->p.transform = identity_matrix();
    m->pattern = 1;
    m->pattern_at = &gradient_pattern;
}

void   ring_pattern_shape(t_color a, t_color b, t_material *m)
{
   m->p.a = a;
   m->p.b = b;
   m->p.transform = identity_matrix();
   m->pattern = 1;
   m->pattern_at = &ring_pattern;
}

void    checker_pattern_shape(t_color a, t_color b, t_material *m)
{
   m->p.a = a;
   m->p.b = b;
   m->p.transform = identity_matrix();
   m->pattern = 1;
   m->pattern_at = &checker_pattern;
}

double  realmod(double x, double p)
{
    if (x < 0)
        return (fmod((fmod(x, p) + p), p));
    else
        return (fmod(x, p));
}

t_color stripe_at(t_pattern p, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (p.a);
    else
        return (p.b);
}
/* //testpattern
t_color stripe_at(t_pattern p, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (color(point.c[0], point.c[1], point.c[2]));
    else
        return (color(point.c[0], point.c[1], point.c[2]));
}*/

t_color gradient_at(t_pattern p, t_vec point)
{
    t_color distance;
    double  fraction;

    distance = sub_col(p.b, p.a);
    fraction = point.c[0] - floor(point.c[0]);
    return (add_col(p.a, mult_col(distance, fraction)));
}

t_color ring_at(t_pattern p, t_vec point)
{
    if (realmod(floor(sqrt((point.c[0] * point.c[0]) + (point.c[2] * point.c[2]))), 2) == 0)
        return (p.a);
    else
        return (p.b);
}

t_color checker_at(t_pattern p, t_vec point)
{
    if ((realmod(floor(point.c[0]) + floor(point.c[1]) + floor(point.c[2]), 2)) == 0)
        return (p.a);
    else
        return (p.b);
}
