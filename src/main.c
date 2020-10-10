/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/10 22:40:12 by sdiego           ###   ########.fr       */
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

int		key_press(t_sdl *sdl, t_camera *camera)
{
	if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
		sdl->run = 1;
	else if (sdl->e.key.keysym.sym == SDLK_F12)
		save_texture("img.bmp", sdl->ren, sdl->text);
	else if (sdl->e.key.keysym.sym == SDLK_1)
	{
		camera->aliasing = camera->aliasing == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	else if (sdl->e.key.keysym.sym == SDLK_2)
	{
		camera->sepia = camera->sepia == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	return (0);
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

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("%s\n", SDL_GetError());
		return (1);
	}
	sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
	{
		printf("%s\n", SDL_GetError());
		return (1);
	}
	// add icon
	sdl->icon = SDL_LoadBMP("icon.bmp");
	SDL_SetWindowIcon(sdl->win, sdl->icon);
	//
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE);
	if (sdl->ren == NULL)
	{
		printf("%s\n", SDL_GetError());
		return (1);
	}
	sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (sdl->text == NULL)
	{
		printf("%s\n", SDL_GetError());
		return (1);
	}
	sdl->img = malloc(WIN_W * WIN_H * sizeof(int));
	if (sdl->img == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	return(0);
}

int		hit(t_x_t x)
{
	int	i;
	int	a;

	i = 0;
	a = -1;
	while (i < x.max_obj)
	{
		if (x.t[i].count > 0 && x.t[i].t >= 0)
		{
			if (a == -1)
				a = i;
			if (x.t[i].t < x.t[a].t)
				a = i;
		}
		i++;
	}
	return (a);
}


int		main(void)
{
	t_sdl		sdl;
	t_world		w;

	if (init(&sdl) != 0)
		quit(&sdl);

	sdl.run = 0;




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
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 1.152);
	c.transform = view_transform(set_v_p(-2.6, 1.5, -3.9, 1), set_v_p(-0.6, 1, -0.8, 1), set_v_p(0, 1, 0, 0));







	sdl.progress = 0;
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			if (sdl.e.type == SDL_KEYDOWN)
				key_press(&sdl, &c);
			/*if (sdl.e.type == SDL_MOUSEMOTION)
				mouse_move(&m);
			if (clear_img(&sdl) != 0)
				sdl.run = 1;
			if (raycast(&sdl) != 0)
				sdl.run = 1;
			if (draw(&sdl) != 0)
				sdl.run = 1;
			SDL_RenderPresent(sdl.ren);*/
		}
		if (sdl.progress == 0)
		{
			render(&sdl, c, w);
			write(1, "Render complite!\n", 17);
			sdl.progress++;
		}
	}
	quit(&sdl);
	return(0);
}
