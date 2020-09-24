/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/20 16:57:38 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

void   checker_pattern_shape(t_color a, t_color b, t_material *m)
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
