/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/28 19:02:35 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		quit(t_sdl *sdl)
{
	if (sdl->text != NULL)
		SDL_DestroyTexture(sdl->text);
	sdl->text = NULL;
	if (sdl->img != NULL)
		free(sdl->img);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();

	return(0);
}

int	clear_img(t_sdl *sdl)
{
	if (SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00) == -1)
	{
		printf("error");
		return (1);
	}
	if (SDL_RenderClear(sdl->ren) == -1)
	{
		printf("error");
		return (1);
	}
	return (0);
}

int		init(t_sdl *sdl)
{
	int i;

	i = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE);
	if (sdl->ren == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (sdl->text == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->img = malloc(WIN_W * WIN_H * sizeof(int));
	if (sdl->img == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	return(i);
}

int		hit(t_x_t x)
{
	int	i;
	int check;
	int	a;
	int	b;

	i = 0;
	check = 0;
	b = 0;
	while (i < x.max_obj)
	{
		if (x.t[i].count > 0 && x.t[i].t >= 0)
		{
			b = 1;
			if (check == 0)
			{
				a = i;
				check++;
			}
			if (x.t[i].t < x.t[a].t)
			{
				a = i;
			}
		}
		i++;
	}
	if (b == 1)
		return (a);
	else
		return (-1); // значит нет пересечений
}

void	alg(t_sdl *sdl, t_world w)
{
	int	x;
	int	y;
	double world_y;
	double	world_x;
	double wall_size = 7;
	double wall_z = 10;
	t_vec ray_org = set_v_p(0,0,-5,1);

	y = 0;
	double pixel_size = wall_size / WIN_H;
	double half = wall_size / 2;
	while (y < WIN_H)
	{
		world_y = half - pixel_size * y;
		x = 0;
		while (x < WIN_W)
		{
			world_x = -half + pixel_size * x;
			t_vec pos = set_v_p(world_x, world_y, wall_z, 1);
			t_ray r = set_ray(ray_org, normalize(sub(pos, ray_org)));
			//raycast(sdl, r, x, y, w);
			x++;
		}
		y++;
	}
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_world		w;

	if (init(&sdl) != 0)
		quit(&sdl);

	sdl.run = 0;

/*

	w.pl[0] = set_plane(0);
	w.pl[0].m.color = color(1, 0.5, 0.5);
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.2;

	w.cone[0] = set_cone();
	w.cone[0].m.color = color(0, 1, 0);
	w.cone[0].transform = matrix_mult(w.cone[0].transform, scaling(0.2, 1, 0.2));
	ring_pattern_cone(color(0,1,0), color(1,0,1), &w.cone[0]);
	w.cone[0].m.p.transform = matrix_mult(w.cone[0].m.p.transform, scaling(0.3, 0.3, 0.3));

	w.cone[1] = set_cone();
	w.cone[1].m.color = color(0, 1, 1);
	w.cone[1].closed = 1;
	w.cone[1].max = 0;
	w.cone[1].min = -1;
	w.cone[1].transform = matrix_mult(w.cone[1].transform, translation(-2, 1, 0));
	gradient_pattern_cone(color(1,1,0), color(0,1,1), &w.cone[1]);
	w.cone[1].m.p.transform = matrix_mult(w.cone[1].m.p.transform, scaling(0.5, 0.5, 0.5));
	//w.cone[1].transform = matrix_mult(w.cone[1].transform, rotation_x(-3.14 / 4));

	w.cone[2] = set_cone();
	w.cone[2].m.color = color(1, 1, 0);
	w.cone[2].closed = 1;
	w.cone[2].max = 1;
	w.cone[2].min = -1;
	w.cone[2].transform = matrix_mult(w.cone[2].transform, translation(2, 1, 0));
	stripe_pattern_cone(color(0,0,0), color(1,1,1), &w.cone[2]);
	w.cone[2].m.p.transform = matrix_mult(w.cone[2].m.p.transform, scaling(0.3, 0.3, 0.3));
	//w.cone[2].transform = matrix_mult(w.cone[2].transform, rotation_x(-3.14 / 4));


	//light
	w.light = point_light(color(1, 1, 1), set_v_p(-10, 2, -10, 1));
	w.pl_obj = 1;
	w.cone_obj = 3;
	w.max_obj = 3;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, &w, &w.pl[i].m);
		i++;
	}
	i = 0;
	while (i < w.cone_obj)
	{
		push_obj((void*)(&w.cone[i]), &normal_at_cone, &intersect_cone, &shade_hit_cone, &w, &w.cone[i].m);
		i++;
	}
//WORLD

	//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));

	render(&sdl, c, w);

*/

/*
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
t_vec p1 = set_v_p(0, 1, 0, 1);
t_vec p2 = set_v_p(-1, 0, 0, 1);
t_vec p3 = set_v_p(1, 0, 0, 1);
w.trian[0] = set_trian(p1, p2, p3);
w.trian[0].m.color = color (1, 0.75, 0.5);
w.trian[0].transform = matrix_mult(w.trian[0].transform, translation(0, 1.5, 0));
//w.trian[0].transform = matrix_mult(w.trian[0].transform, rotation_x(3.14 / 2));
w.trian[0].transform = matrix_mult(w.trian[0].transform, scaling(1.5, 1.5, 1.5));
w.trian_obj = 1;
w.light = point_light(color(1, 1, 1), set_v_p(-10, 2, -10, 1));
w.ar_count = 0;
int i = 0;
	while (i < w.trian_obj)
	{
		push_obj((void*)(&w.trian[i]), &normal_at_trian, &intersect_trian, &shade_hit_trian, &w, &w.trian[i].m);
		i++;
	}
//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));

	//render(&sdl, c, w);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


/*

//CH 11//
//
	//floor
	w.pl[0] = set_plane();
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.4;
	w.pl[0].transform = matrix_mult(w.pl[0].transform, rotation_y(0.31415));
	checker_pattern_shape(color(0.35, 0.35, 0.35), color(0.65,0.65,0.65), &w.pl[0].m);

	//ceiling
	w.pl[1] = set_plane();
	w.pl[1].transform = matrix_mult(w.pl[1].transform, translation(0,5,0));
	w.pl[1].m.color = color(0.8, 0.8, 0.8);
	w.pl[1].m.specular = 0;
	w.pl[1].m.ambient = 0.3;

	// west wall
	w.pl[2] = set_plane();
	w.pl[2].transform = matrix_mult(w.pl[2].transform, translation(-5, 0, 0));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_z(1.5708));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[2].m);
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, rotation_y(1.5708));
	w.pl[2].m.ambient = 0;
	w.pl[2].m.diffuse = 0.4;
	w.pl[2].m.specular = 0;
	w.pl[2].m.reflective = 0.3;

	//east wall
	w.pl[3] = set_plane();
	w.pl[3].transform = matrix_mult(w.pl[3].transform, translation(5, 0, 0));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_z(1.5708));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[3].m);
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, rotation_y(1.5708));
	w.pl[3].m.ambient = 0;
	w.pl[3].m.diffuse = 0.4;
	w.pl[3].m.specular = 0;
	w.pl[3].m.reflective = 0.3;

	//north wall
	w.pl[4] = set_plane();
	w.pl[4].transform = matrix_mult(w.pl[4].transform, translation(0, 0, 5));
	w.pl[4].transform = matrix_mult(w.pl[4].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[4].m);
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, rotation_y(1.5708));
	w.pl[4].m.ambient = 0;
	w.pl[4].m.diffuse = 0.4;
	w.pl[4].m.specular = 0;
	w.pl[4].m.reflective = 0.3;

	//south wall
	w.pl[5] = set_plane();
	w.pl[5].transform = matrix_mult(w.pl[5].transform, translation(0, 0, -5));
	w.pl[5].transform = matrix_mult(w.pl[5].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[5].m);
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, rotation_y(1.5708));
	w.pl[5].m.ambient = 0;
	w.pl[5].m.diffuse = 0.4;
	w.pl[5].m.specular = 0;
	w.pl[5].m.reflective = 0.3;


	//background ball
	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(4.6, 0.4, 1));
	w.s[0].transform = matrix_mult(w.s[0].transform, scaling(0.4, 0.4, 0.4));
	w.s[0].m.color = (color(0.8, 0.5, 0.3));
	w.s[0].m.shininess = 50;


	//background ball
	w.s[1] = set_sphere();
	w.s[1].transform = matrix_mult(w.s[1].transform, translation(4.7, 0.3, 0.4));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(0.3,0.3,0.3));

	w.s[1].m.color = (color(0.9, 0.4, 0.5));
	w.s[1].m.shininess = 50;


	//background ball
	w.s[2] = set_sphere();
	w.s[2].transform = matrix_mult(w.s[2].transform, translation(-1, 0.5, 4.5));
	w.s[2].transform = matrix_mult(w.s[2].transform, scaling(0.5, 0.5, 0.5));
	w.s[2].m.color = (color(0.4, 0.9, 0.6));
	w.s[2].m.shininess = 50;


	//background ball
	w.s[3] = set_sphere();
	w.s[3].transform =  matrix_mult(w.s[3].transform, translation(-1.7, 0.3, 4.7));
	w.s[3].transform = matrix_mult(w.s[3].transform, scaling(0.3 ,0.3, 0.3));

	w.s[3].m.color = (color(0.4, 0.6, 0.9));
	w.s[3].m.shininess = 50;

	//foreground balls

	//red
	w.s[4] = set_sphere();
	w.s[4].transform =  matrix_mult(w.s[4].transform, translation(-0.6, 1, 0.6));
	w.s[4].m.color = (color(1, 0.3, 0.2));
	w.s[4].m.specular = 0.4;
	w.s[4].m.shininess = 5;
	//checker_pattern_shape(color(0.35, 0.35, 0.35), color(0.65,0.65,0.65), &w.s[4].m);
	//w.s[4].m.p.transform = matrix_mult(w.s[4].m.p.transform, scaling(0.25, 0.25, 0.25));

	//blue glass
	w.s[5] = set_sphere();
	w.s[5].transform =  matrix_mult(w.s[5].transform, translation(0.6, 0.7, -0.6));
	w.s[5].transform = matrix_mult(w.s[5].transform, scaling(0.7,0.7,0.7));

	w.s[5].m.color = (color(0, 0, 0.2));
	w.s[5].m.ambient = 0;
	w.s[5].m.diffuse = 0.4;
	w.s[5].m.specular = 0.9;
	w.s[5].m.shininess = 300;
	w.s[5].m.reflective = 0.9;
	w.s[5].m.transparency = 0.9;
	w.s[5].m.refractive_index = 1.5;

	//green glass
	w.s[6] = set_sphere();
	w.s[6].transform =  matrix_mult(w.s[6].transform, translation(-0.7, 0.5, -0.8));
	w.s[6].transform = matrix_mult(w.s[6].transform, scaling(0.5,0.5,0.5));

	w.s[6].m.color = (color(0, 0.2, 0));
	w.s[6].m.ambient = 0;
	w.s[6].m.diffuse = 0.4;
	w.s[6].m.specular = 0.9;
	w.s[6].m.shininess = 300;
	w.s[6].m.reflective = 0.9;
	w.s[6].m.transparency = 0.9;
	w.s[6].m.refractive_index = 1.5;

	//light
	w.light_obj = 1;
	w.light[0] = point_light(color(1, 1, 1), set_v_p(-4.9, 4.9, -1, 1));
	w.light[1] = point_light(color(1, 1, 1), set_v_p(4.9, 4.9, -1, 1));

	w.s_obj = 7;
	w.pl_obj = 6;
	w.max_obj = 13;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 1.152);
	c.transform = view_transform(set_v_p(-2.6, 1.5, -3.9, 1), set_v_p(-0.6, 1, -0.8, 1), set_v_p(0, 1, 0, 0));

*/

/*
	default_world(&w);
	//w.light[0] = point_light(color(1,1,1), set_v_p(-10,-10,-10,1));
	//t_vec light_position = set_v_p(-10, -10, -10, 1);
	w.ar_count = 1;
	w.s[0].m.ambient = 0.1;
	w.s[0].m.diffuse = 0.9;
	w.s[0].m.specular = 0;
	w.s[0].m.color = color(1, 1, 1);
	w.s[0].m.pattern = 0;

	t_vec point = set_v_p(0, 0, -1, 1);
	t_vec eyev = set_v_p(0, 0, -1, 0);
	t_vec normalv = set_v_p(0, 0, -1, 0);
	w.light_count = 0;
	w.light[0] = point_light(color(1, 1, 1), set_v_p(0, 0, -10, 1));
	t_comps c;
	c.eyev = eyev;
	c.normalv = normalv;
	c.point = point;
	c.shadow = 1.0;
	c.obj = 0;
	c.over_point = add(c.point, mult(c.normalv, EPSILON));
	t_color result = lighting(&w.s[0].m, w, c);
	printf("r %f , g %f, b %f\n", result.r ,result.g, result.b);
*/

/*
	default_world(&w);

	w.light_count = 0;
	t_vec corner = set_v_p(0, 0, 0, 1);
	t_vec v1 = set_v_p(2, 0, 0, 0);
	t_vec v2 = set_v_p(0, 0, 1, 0);
	w.light[0] = area_light(corner, v1, 4 ,v2 ,2, color(1, 1, 1));
	w.light[0].jetter[0] = 0.3;
	w.light[0].jetter[1] = 0.7;


	t_vec pt = point_on_light(&w.light[0], 0, 0);
	printf("%f\n %f\n\n", pt.c[0], pt.c[2]);

	pt = point_on_light(&w.light[0], 1, 0);
	printf("%f\n %f\n\n", pt.c[0], pt.c[2]);

	pt = point_on_light(&w.light[0], 0, 1);
	printf("%f\n %f\n\n", pt.c[0], pt.c[2]);

	pt = point_on_light(&w.light[0], 2, 0);
	printf("%f\n %f\n\n", pt.c[0], pt.c[2]);

	pt = point_on_light(&w.light[0], 3, 1);
	printf("%f\n %f\n\n", pt.c[0], pt.c[2]);


	exit(0);

	default_world(&w);

	w.light_count = 0;
	t_vec corner = set_v_p(-0.5, -0.5, -5, 1);
	t_vec v1 = set_v_p(1, 0, 0, 0);
	t_vec v2 = set_v_p(0, 1, 0, 0);
	w.light[0] = area_light(corner, v1, 2 ,v2 ,2, color(1, 1, 1));
	w.light[0].jetter[0] = 0.7;
	w.light[0].jetter[1] = 0.3;
	w.light[0].jetter[2] = 0.9;
	w.light[0].jetter[3] = 0.1;
	w.light[0].jetter[4] = 0.5;

	t_vec pt = set_v_p(0,0,2,1);
	double intensity = intensity_at(w, pt);
	printf("%f\n", intensity);

	pt = set_v_p(1,-1,2,1);
	intensity = intensity_at(w, pt);
	printf("%f\n", intensity);

	pt = set_v_p(1.5,0,2,1);
	intensity = intensity_at(w, pt);
	printf("%f\n", intensity);

	pt = set_v_p(1.25,1.25,3,1);
	intensity = intensity_at(w, pt);
	printf("%f\n", intensity);

	pt = set_v_p(0,0,-2,1);
	intensity = intensity_at(w, pt);
	printf("%f\n", intensity);

	exit(0);
*/
/*
	default_world(&w);
	w.ar_count = 1;
	w.light_count = 0;
	t_vec corner = set_v_p(-0.5, -0.5, -5, 1);
	t_vec v1 = set_v_p(1, 0, 0, 0);
	t_vec v2 = set_v_p(0, 1, 0, 0);
	w.light[0] = area_light(corner, v1, 2 ,v2 ,2, color(1, 1, 1));
	w.s[0].m.ambient = 0.1;
	w.s[0].m.diffuse = 0.9;
	w.s[0].m.specular = 0;
	w.s[0].m.color = color(1,1,1);

	t_vec eye = set_v_p(0, 0, -5, 1);
	t_vec pt = set_v_p(0, 0, -1, 1);
	t_vec eyev = normalize(sub(eye, pt));
	t_vec normalv = set_v_p(pt.c[0], pt.c[1], pt.c[2], 0);

	t_comps c;
	c.eyev = eyev;
	c.normalv = normalv;
	c.point = pt;
	c.shadow = 1.0;
	c.obj = 0;
	c.over_point = add(c.point, mult(c.normalv, EPSILON));

	t_color result = lighting(&w.s[0].m, w, c);
	printf("r %f , g %f, b %f\n", result.r ,result.g, result.b);

	exit(0);
*/

	//CH 12//
//

//floor / ceiling
w.cub[0] = set_cube();
w.cub[0].transform = matrix_mult(w.cub[0].transform, scaling(20, 7, 20));
w.cub[0].transform = matrix_mult(w.cub[0].transform, translation(0, 1, 0));
checker_pattern_shape(color(0, 0, 0), color(0.25, 0.25, 0.25), &w.cub[0].m);
w.cub[0].m.p.transform = matrix_mult(w.cub[0].m.p.transform, scaling(0.07, 0.07, 0.07));
w.cub[0].m.ambient = 0.25;
w.cub[0].m.diffuse = 0.7;
w.cub[0].m.specular = 0.9;
w.cub[0].m.shininess = 300;
w.cub[0].m.reflective = 0.1;

//walls
w.cub[1] = set_cube();
w.cub[1].transform = matrix_mult(w.cub[1].transform, scaling(10, 10, 10));
checker_pattern_shape(color(0.4863, 0.3765, 0.2941), color(0.3725, 0.2902, 0.2275), &w.cub[1].m);
w.cub[1].m.p.transform = matrix_mult(w.cub[1].m.p.transform, scaling(0.05, 20, 0.05));
w.cub[1].m.ambient = 0.1;
w.cub[1].m.diffuse = 0.7;
w.cub[1].m.specular = 0.9;
w.cub[1].m.shininess = 300;
w.cub[1].m.reflective = 0.1;

//table top
w.cub[2] = set_cube();
w.cub[2].transform = matrix_mult(w.cub[2].transform, translation(0, 3.1, 0));
w.cub[2].transform = matrix_mult(w.cub[2].transform, scaling(3, 0.1, 2));
stripe_pattern_shape(color(0.5529, 0.4235, 0.3255), color(0.6588, 0.5098, 0.4000), &w.cub[2].m);
w.cub[2].m.p.transform = matrix_mult(w.cub[2].m.p.transform, scaling(0.05, 0.05, 0.05));
w.cub[2].m.p.transform = matrix_mult(w.cub[2].m.p.transform, rotation_y(0.1));
w.cub[2].m.ambient = 0.1;
w.cub[2].m.diffuse = 0.7;
w.cub[2].m.specular = 0.9;
w.cub[2].m.shininess = 300;
w.cub[2].m.reflective = 0.2;

//leg #1
w.cub[3] = set_cube();
w.cub[3].transform = matrix_mult(w.cub[3].transform, translation(2.7, 1.5, -1.7));
w.cub[3].transform = matrix_mult(w.cub[3].transform, scaling(0.1, 1.5, 0.1));
w.cub[3].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[3].m.ambient = 0.2;
w.cub[3].m.diffuse = 0.7;

//leg #2
w.cub[4] = set_cube();
w.cub[4].transform = matrix_mult(w.cub[4].transform, translation(2.7, 1.5, 1.7));
w.cub[4].transform = matrix_mult(w.cub[4].transform, scaling(0.1, 1.5, 0.1));
w.cub[4].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[4].m.ambient = 0.2;
w.cub[4].m.diffuse = 0.7;

//leg #3
w.cub[5] = set_cube();
w.cub[5].transform = matrix_mult(w.cub[5].transform, translation(-2.7, 1.5, -1.7));
w.cub[5].transform = matrix_mult(w.cub[5].transform, scaling(0.1, 1.5, 0.1));
w.cub[5].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[5].m.ambient = 0.2;
w.cub[5].m.diffuse = 0.7;

//leg #4
w.cub[6] = set_cube();
w.cub[6].transform = matrix_mult(w.cub[6].transform, translation(-2.7, 1.5, 1.7));
w.cub[6].transform = matrix_mult(w.cub[6].transform, scaling(0.1, 1.5, 0.1));
w.cub[6].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[6].m.ambient = 0.2;
w.cub[6].m.diffuse = 0.7;

//glass cube
w.cub[7] = set_cube();
w.cub[7].transform = matrix_mult(w.cub[7].transform, translation(0, 3.45001, 0));
w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_y(0.2));
w.cub[7].transform = matrix_mult(w.cub[7].transform, scaling(0.25, 0.25, 0.25));
w.cub[7].m.color = color(1, 1, 0.8);
w.cub[7].m.ambient = 0;
w.cub[7].m.diffuse = 0.3;
w.cub[7].m.specular = 0.9;
w.cub[7].m.shininess = 300;
w.cub[7].m.reflective = 0.7;
w.cub[7].m.transparency = 0.7;
w.cub[7].m.refractive_index = 1.5;
w.cub[7].m.shadow = 0;

//little cube #1
w.cub[8] = set_cube();
w.cub[8].transform = matrix_mult(w.cub[8].transform, translation(1, 3.35, -0.9));
w.cub[8].transform = matrix_mult(w.cub[8].transform, scaling(0.15, 0.15, 0.15));
w.cub[8].transform = matrix_mult(w.cub[8].transform, rotation_y(-0.4));
w.cub[8].m.color = color(1, 0.5, 0.5);
w.cub[8].m.reflective = 0.6;
w.cub[8].m.diffuse = 0.4;

//little cube #2
w.cub[9] = set_cube();
w.cub[9].transform = matrix_mult(w.cub[9].transform, translation(-1.5, 3.27, 0.3));
w.cub[9].transform = matrix_mult(w.cub[9].transform, rotation_y(0.4));
w.cub[9].transform = matrix_mult(w.cub[9].transform, scaling(0.15, 0.07, 0.15));
w.cub[9].m.color = color(1, 1, 0.5);

//little cube #3
w.cub[10] = set_cube();
w.cub[10].transform = matrix_mult(w.cub[10].transform, translation(0, 3.25, 1));
w.cub[10].transform = matrix_mult(w.cub[10].transform, rotation_y(0.4));
w.cub[10].transform = matrix_mult(w.cub[10].transform, scaling(0.2, 0.05, 0.05));
w.cub[10].m.color = color(0.5, 1, 0.5);

//little cube #4
w.cub[11] = set_cube();
w.cub[11].transform = matrix_mult(w.cub[11].transform, translation(-0.6, 3.4, -1));
w.cub[11].transform = matrix_mult(w.cub[11].transform, rotation_y(0.8));
w.cub[11].transform = matrix_mult(w.cub[11].transform, scaling(0.05, 0.2, 0.05));
w.cub[11].m.color = color(0.5, 0.5, 1);

//little cube #5
w.cub[12] = set_cube();
w.cub[12].transform = matrix_mult(w.cub[12].transform, translation(2, 3.4, 1));
w.cub[12].transform = matrix_mult(w.cub[12].transform, rotation_y(0.8));
w.cub[12].transform = matrix_mult(w.cub[12].transform, scaling(0.05, 0.2, 0.05));
w.cub[12].m.color = color(0.5, 1, 1);

//frame #1
w.cub[13] = set_cube();
w.cub[13].transform = matrix_mult(w.cub[13].transform, translation(-10, 4, 1));
w.cub[13].transform = matrix_mult(w.cub[13].transform, scaling(0.05, 1, 1));
w.cub[13].m.color = color(0.7098, 0.2471, 0.2196);
w.cub[13].m.diffuse = 0.6;

//frame #2
w.cub[14] = set_cube();
w.cub[14].transform = matrix_mult(w.cub[14].transform, translation(-10, 3.4, 2.7));
w.cub[14].transform = matrix_mult(w.cub[14].transform, scaling(0.05, 0.4, 0.4));
w.cub[14].m.color = color(0.2667, 0.2706, 0.6902);
w.cub[14].m.diffuse = 0.6;

//frame #3
w.cub[15] = set_cube();
w.cub[15].transform = matrix_mult(w.cub[15].transform, translation(-10, 4.6, 2.7));
w.cub[15].transform = matrix_mult(w.cub[15].transform, scaling(0.05, 0.4, 0.4));
w.cub[15].m.color = color(0.3098, 0.5961, 0.3098);
w.cub[15].m.diffuse = 0.6;

//mirror frame
w.cub[16] = set_cube();
w.cub[16].transform = matrix_mult(w.cub[16].transform, translation(-2, 3.5, 9.95));
w.cub[16].transform = matrix_mult(w.cub[16].transform, scaling(5, 1.5, 0.05));
w.cub[16].m.color = color(0.3882, 0.2627, 0.1882);
w.cub[16].m.diffuse = 0.7;

//mirror
w.cub[17] = set_cube();
w.cub[17].transform = matrix_mult(w.cub[17].transform, translation(-2, 3.5, 9.95));
w.cub[17].transform = matrix_mult(w.cub[17].transform, scaling(4.8, 1.4, 0.06));
w.cub[17].m.color = color(0, 0, 0);
w.cub[17].m.diffuse = 0;
w.cub[17].m.ambient = 0;
w.cub[17].m.specular = 1;
w.cub[17].m.shininess = 300;
w.cub[17].m.reflective = 1;

//light
w.light_obj = 1;
w.light[0] = point_light(color(1, 1, 0.9), set_v_p(0, 6.9, -5, 1));
w.cub_obj = 18;
w.max_obj = 18;
w.ar_count = 0;
int i = 0;
while (i < w.max_obj)
{
	push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
	i++;
}

t_camera c = camera(WIN_W, WIN_H, 0.785);
c.transform = view_transform(set_v_p(8, 6, -8, 1), set_v_p(0, 3, 0, 1), set_v_p(0, 1, 0, 0));

/*
** TEXTURE mapping
*/

/*
	t_pattern checkers = uv_checkers(2, 2, color(0, 0, 0), color(1, 1, 1));
	t_color color = uv_patter_at(checkers, 0.0, 0.0);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_patter_at(checkers, 0.5, 0.0);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_patter_at(checkers, 0.0, 0.5);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_patter_at(checkers, 0.5, 0.5);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_patter_at(checkers, 1.0, 1.0);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);
*/

/*
	t_vec p = set_v_p(1, 0, 0, 1);
	t_vec uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0, 0, 1, 1);
	uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(-1, 0, 0, 1);
	uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);


	p = set_v_p(0, 1, 0, 1);
	uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0, -1, 0, 1);
	uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(sqrt(2)/2, sqrt(2)/2, 0, 1);
	uv = spherical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);
*/
/*
	t_pattern checkers = uv_checkers(16, 8, color(0, 0, 0), color(1, 1, 1));
	t_texturemap pattern = texture_map(checkers, &spherical_map);
	t_vec point = set_v_p(0.4315, 0.4670, 0.7719, 1);
	t_color color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(-0.9654, 0.2552, -0.0534, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(0.1039, 0.7090, 0.6975, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(-0.4986, -0.7856, -0.3663, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(-0.0317, -0.9395, 0.3411, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(0.4809, -0.7721, 0.4154, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(0.0285, -0.9612, -0.2745, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(-0.5734, -0.2162, -0.7903, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(0.7688, -0.1470, 0.6223, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	point = set_v_p(-0.7652, 0.2175, 0.6060, 1);
	color = pattern_at(pattern, point);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);


	exit(0);
*/

/*
	t_vec p = set_v_p(0, 0, -1, 1);
	t_vec uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0, 0.5, -1, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0, 1, -1, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0.70711, 0.5, -0.70711, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(1, 0.5, 0, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0.70711, 0.5, 0.70711, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(0, -0.25, 1, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(-0.70711, 0.5, 0.70711, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(-1, 1.25, 0, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	p = set_v_p(-0.70711, 0.5, -0.70711, 1);
	uv = cylindrical_map(p);
	printf("u = %f\nv = %f\n\n", uv.c[0], uv.c[1]);

	exit(0);
*/
/*
	t_color main = color(1, 1, 1);
	t_color ul = color(1, 0, 0);
	t_color ur = color(1, 1, 0);
	t_color bl = color(0, 1, 0);
	t_color br = color(0, 1, 1);
	t_pattern p;
	p = uv_align_check(p, main, ul, ur, bl ,br);
	t_color color = uv_pattern_at_cube(p, 0.5, 0.5);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_pattern_at_cube(p, 0.1, 0.9);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_pattern_at_cube(p, 0.9, 0.9);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_pattern_at_cube(p, 0.1, 0.1);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);

	color = uv_pattern_at_cube(p, 0.9, 0.1);
	printf("r = %f\ng = %f\nb = %f\n\n", color.r, color.g, color.b);
	exit(0);
*/

	/*
	SDL_UpdateTexture(sdl.text, NULL, sdl.img, WIN_W * (sizeof(int)));
	SDL_RenderClear(sdl.ren);
	SDL_RenderCopy(sdl.ren, sdl.text, NULL, NULL);
	SDL_RenderPresent(sdl.ren);
	*/
	int progress = 0;
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			/*if (sdl.e.type == SDL_KEYDOWN)
				key_press(&m);
			if (sdl.e.type == SDL_MOUSEMOTION)
				mouse_move(&m);*/
			/*if (clear_img(&sdl) != 0)
				sdl.run = 1;
			if (raycast(&sdl) != 0)
				sdl.run = 1;
			if (draw(&sdl) != 0)
				sdl.run = 1;
			SDL_RenderPresent(sdl.ren);*/
		}
		if (progress == 0)
		{
			render(&sdl, c, w);
			progress++;
		}
	}
	quit(&sdl);
	return(0);
}
