/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/10 19:59:08 by sdiego           ###   ########.fr       */
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


int		main(void)
{
	t_sdl		sdl;
	t_world		w;

	if (init(&sdl) != 0)
		quit(&sdl);

	sdl.run = 0;




// EARTH

	w.pl[0] = set_plane();
	w.pl[0].m.color = color(1, 1, 1);
	w.pl[0].m.ambient = 0;
	w.pl[0].m.specular = 0;
	w.pl[0].m.diffuse = 0.1;
	w.pl[0].m.reflective = 0.4;

	w.cyl[0] = set_cylinder();
	w.cyl[0].min = 0;
	w.cyl[0].max = 0.1;
	w.cyl[0].closed = 1;
	w.cyl[0].m.color = color(1, 1, 1);
	w.cyl[0].m.ambient = 0;
	w.cyl[0].m.specular = 0;
	w.cyl[0].m.diffuse = 0.2;
	w.cyl[0].m.reflective = 0.1;

	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(0, 1.1, 0));
	w.s[0].transform = matrix_mult(w.s[0].transform, rotation_y(1.9));

	w.s[0].m.pattern = 1;
	w.s[0].m.p = uv_checkers(20, 10, color(0, 0.5, 0), color(1, 1, 1));
	w.s[0].m.pattern_at = &pattern_at;
	w.s[0].m.p.transform = identity_matrix();
	w.s[0].m.texture = SDL_LoadBMP("textures/earthmap1k.bmp");
	w.s[0].m.tex = 1;
	w.s[0].m.texturemap = texture_map(w.s[0].m.p, &spherical_map);
	w.s[0].m.ambient = 0.1;
	w.s[0].m.specular = 0.1;
	w.s[0].m.diffuse = 0.9;
	w.s[0].m.shininess = 10;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-100, 100, -100, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.s_obj = 1;
	w.pl_obj = 1;
	w.cyl_obj = 1;
	w.ar_count = 0;

	int i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	i = 0;
	while (i < w.pl_obj)
	{
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}

	i = 0;
	while (i < w.cyl_obj)
	{
		if (check_transform_matrix(w.cyl[i].transform, w.cyl[i].m.p.transform, w.cyl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cyl[i]), &normal_at_cyl, &intersect_cyl, &w, &w.cyl[i].m, &w.cyl[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.8);
	c.transform = view_transform(set_v_p(1, 2, -10, 1), set_v_p(0, 1.1, 0, 1), set_v_p(0, 1, 0, 0));







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
