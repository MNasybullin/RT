/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: out-nasybullin-mr <out-nasybullin-mr@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/23 18:23:41 by out-nasybul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color uv_patter_at_texture(SDL_Surface *texture, double u, double v)
{
    v = 1 - v;
    double x;
    double y;

    x = u * (texture->w - 1);
    y = v * (texture->h - 1);
    return (get_color_tex(texture, round(x), round(y)));    // (int) вместо round()
}

void	uv_checkers(t_uv_check c, t_pattern *p)
{
    //ft_putendl("start of uv_checkers");
    p->a = c.color_a;
    p->b = c.color_b;
    p->height = c.height;
    p->width = c.width;
    //ft_putendl("end of uv_checkers");
}

t_vec cube_uv_front(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(point.c[0] + 1, 2) / 2;
    v = realmod(point.c[1] + 1, 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec cube_uv_back(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(1 - point.c[0], 2) / 2;
    v = realmod(point.c[1] + 1, 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec cube_uv_left(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(point.c[2] + 1, 2) / 2;
    v = realmod(point.c[1] + 1, 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec cube_uv_right(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(1 - point.c[2], 2) / 2;
    v = realmod(point.c[1] + 1, 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec cube_uv_up(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(point.c[0] + 1, 2) / 2;
    v = realmod(1 - point.c[2], 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec cube_uv_down(t_vec point)
{
    t_vec uv;
    double u;
    double v;

    u = realmod(point.c[0] + 1, 2) / 2;
    v = realmod(point.c[2] + 1, 2) / 2;
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

/*
** Identifying the face of a cube from a point
*/

int face_from_point(t_vec point)
{
    double abs_x = fabs(point.c[0]);
    double abs_y = fabs(point.c[1]);
    double abs_z = fabs(point.c[2]);
    double coord = max(abs_x, abs_y, abs_z);

    if (coord == point.c[0])
        return (0); // right
    if (coord == -point.c[0])
        return (1); // left
    if (coord == point.c[1])
        return (2); // up
    if (coord == -point.c[1])
        return (3); // down
    if (coord == point.c[2])
        return (4); // front
    return (5); //back
}

t_pattern uv_align_check(t_color main, t_color ul, t_color ur, t_color bl, t_color br, int face)
{
    t_pattern p;

    p.main[face] = main;
    p.ul[face] = ul;
    p.ur[face] = ur;
    p.bl[face] = bl;
    p.br[face] = br;
    return (p);
}

t_color uv_pattern_at_cube(t_pattern pattern, double u, double v, int face)
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

t_color pattern_at_cube_texture(t_material m, t_vec point)
{
    int face = face_from_point(point);
    t_vec uv;

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

t_color pattern_at_cube(t_material m, t_vec point)
{
    int face = face_from_point(point);
    t_vec uv;

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




t_color uv_patter_at(t_pattern checkers, double u, double v)
{
    double u2;
    double v2;

    u2 = floor(u * (double)checkers.width);
    v2 = floor(v * (double)checkers.height);
    if (realmod((u2 + v2), 2) == 0)
        return(checkers.a);
    else
        return(checkers.b);
}

t_vec   cylindrical_map(t_vec p)
{
    double theta;
    double raw_u;
    double u;
    double v;
    t_vec uv;

    theta = atan2(p.c[0], p.c[2]);
    raw_u = theta / (2 * M_PI);
    u = 1 - (raw_u + 0.5);
    v = realmod(p.c[1], 1);
    uv = set_v_p(u, v, 0, 0);
    return (uv);
}

t_vec   planar_map(t_vec p)
{
    double u;
    double v;
    t_vec uv;

    u = realmod(p.c[0], 1);
    v = realmod(p.c[2], 1);
    uv = set_v_p(u, v, 0, 0);
    return (uv);
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
t_color pattern_at(t_material m, t_vec point)
{
    t_vec uv;
    t_color color;

    uv = (m.texturemap.uv_map)(point);
    if (m.tex == 1)
        color = uv_patter_at_texture(m.texture, uv.c[0], uv.c[1]);
    else
        color = uv_patter_at(m.texturemap.uv_pattern, uv.c[0], uv.c[1]);
    return (color);
}

t_vec world_point_to_pattern_point(t_pattern p, t_matrix transform, t_vec world_point)
{
    t_vec	obj_point;
	t_vec	pattern_point;

	obj_point = matrix_mult_v_p(matrix_inverse(transform), world_point);

	pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);

	return (pattern_point);
}

/*
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
*/
void   stripe_pattern_shape(t_color a, t_color b, t_material *m)
{
    m->p.a = a;
    m->p.b = b;
    //m->p.transform = identity_matrix();
    m->pattern = 1;
    m->pattern_at = &stripe_at;
}

void   gradient_pattern_shape(t_color a, t_color b, t_material *m)
{
    m->p.a = a;
    m->p.b = b;
    //m->p.transform = identity_matrix();
    m->pattern = 1;
    m->pattern_at = &gradient_at;
}

void   ring_pattern_shape(t_color a, t_color b, t_material *m)
{
   m->p.a = a;
   m->p.b = b;
   //m->p.transform = identity_matrix();
   m->pattern = 1;
   m->pattern_at = &ring_at;
}

void    checker_pattern_shape(t_color a, t_color b, t_material *m)
{
   m->p.a = a;
   m->p.b = b;
   //m->p.transform = identity_matrix();
   m->pattern = 1;
   m->pattern_at = &checker_at;
}

double  realmod(double x, double p)
{
    if (x < 0)
        return (fmod((fmod(x, p) + p), p));
    else
        return (fmod(x, p));
}

t_color stripe_at(t_material m, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (m.p.a);
    else
        return (m.p.b);
}
/* //testpattern
t_color stripe_at(t_pattern p, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (color(point.c[0], point.c[1], point.c[2]));
    else
        return (color(point.c[0], point.c[1], point.c[2]));
}*/

t_color gradient_at(t_material m, t_vec point)
{
    t_color distance;
    double  fraction;

    distance = sub_col(m.p.b, m.p.a);
    fraction = point.c[0] - floor(point.c[0]);
    return (add_col(m.p.a, mult_col(distance, fraction)));
}

t_color ring_at(t_material m, t_vec point)
{
    if (realmod(floor(sqrt((point.c[0] * point.c[0]) + (point.c[2] * point.c[2]))), 2) == 0)
        return (m.p.a);
    else
        return (m.p.b);
}

t_color checker_at(t_material m, t_vec point)
{
    if ((realmod(floor(point.c[0]) + floor(point.c[1]) + floor(point.c[2]), 2)) == 0)
        return (m.p.a);
    else
        return (m.p.b);
}
