/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/07 19:07:34 by sdiego           ###   ########.fr       */
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




// Texture mapping
// cube
	t_color red = color(1, 0, 0);
	t_color yellow = color(1, 1, 0);
	t_color brown = color(1, 0.5, 0);
	t_color green = color(0, 1, 0);
	t_color cyan = color(0, 1, 1);
	t_color blue = color(0, 0, 1);
	t_color purple = color(1, 0, 1);
	t_color white = color(1, 1, 1);
	t_pattern pattern;
	pattern = uv_align_check(yellow, cyan, red, blue, brown, 1);
	pattern = uv_align_check(cyan, red, yellow, brown, green, 4);
    pattern = uv_align_check(red, yellow, purple, green, white, 0);
    pattern = uv_align_check(green, purple, cyan, white, blue, 5);
    pattern = uv_align_check(brown, cyan, purple, red, yellow, 2);
    pattern = uv_align_check(purple, brown, green, blue, white, 3);

	w.cub[0] = set_cube();
	w.cub[0].transform = matrix_mult(w.cub[0].transform, translation(-6, 2, 0));
	w.cub[0].transform = matrix_mult(w.cub[0].transform, rotation_x(0.7854));
	w.cub[0].transform = matrix_mult(w.cub[0].transform, rotation_y(0.7854));
	w.cub[0].m.pattern = 1;
	w.cub[0].m.p = pattern;
	w.cub[0].m.p.transform = identity_matrix();
	w.cub[0].m.pattern_at = &pattern_at_cube;
	w.cub[0].m.ambient = 0.2;
	w.cub[0].m.specular = 0;
	w.cub[0].m.diffuse = 0.8;

	w.cub[1] = set_cube();
	w.cub[1].transform = matrix_mult(w.cub[1].transform, translation(-2, 2, 0));
	w.cub[1].transform = matrix_mult(w.cub[1].transform, rotation_x(0.7854));
	w.cub[1].transform = matrix_mult(w.cub[1].transform, rotation_y(2.3562));
	w.cub[1].m.pattern = 1;
	w.cub[1].m.p = pattern;
	w.cub[1].m.p.transform = identity_matrix();
	w.cub[1].m.pattern_at = &pattern_at_cube;
	w.cub[1].m.ambient = 0.2;
	w.cub[1].m.specular = 0;
	w.cub[1].m.diffuse = 0.8;

	w.cub[2] = set_cube();
	w.cub[2].transform = matrix_mult(w.cub[2].transform, translation(2, 2, 0));
	w.cub[2].transform = matrix_mult(w.cub[2].transform, rotation_x(0.7854));
	w.cub[2].transform = matrix_mult(w.cub[2].transform, rotation_y(3.927));
	w.cub[2].m.pattern = 1;
	w.cub[2].m.p = pattern;
	w.cub[2].m.p.transform = identity_matrix();
	w.cub[2].m.pattern_at = &pattern_at_cube;
	w.cub[2].m.ambient = 0.2;
	w.cub[2].m.specular = 0;
	w.cub[2].m.diffuse = 0.8;

	w.cub[3] = set_cube();
	w.cub[3].transform = matrix_mult(w.cub[3].transform, translation(6, 2, 0));
	w.cub[3].transform = matrix_mult(w.cub[3].transform, rotation_x(0.7854));
	w.cub[3].transform = matrix_mult(w.cub[3].transform, rotation_y(5.4978));
	w.cub[3].m.pattern = 1;
	w.cub[3].m.p = pattern;
	w.cub[3].m.p.transform = identity_matrix();
	w.cub[3].m.pattern_at = &pattern_at_cube;
	w.cub[3].m.ambient = 0.2;
	w.cub[3].m.specular = 0;
	w.cub[3].m.diffuse = 0.8;

	w.cub[4] = set_cube();
	w.cub[4].transform = matrix_mult(w.cub[4].transform, translation(-6, -2, 0));
	w.cub[4].transform = matrix_mult(w.cub[4].transform, rotation_x(-0.7854));
	w.cub[4].transform = matrix_mult(w.cub[4].transform, rotation_y(0.7854));
	w.cub[4].m.pattern = 1;
	w.cub[4].m.p = pattern;
	w.cub[4].m.p.transform = identity_matrix();
	w.cub[4].m.pattern_at = &pattern_at_cube;
	w.cub[4].m.ambient = 0.2;
	w.cub[4].m.specular = 0;
	w.cub[4].m.diffuse = 0.8;

	w.cub[5] = set_cube();
	w.cub[5].transform = matrix_mult(w.cub[5].transform, translation(-2, -2, 0));
	w.cub[5].transform = matrix_mult(w.cub[5].transform, rotation_x(-0.7854));
	w.cub[5].transform = matrix_mult(w.cub[5].transform, rotation_y(2.3562));
	w.cub[5].m.pattern = 1;
	w.cub[5].m.p = pattern;
	w.cub[5].m.p.transform = identity_matrix();
	w.cub[5].m.pattern_at = &pattern_at_cube;
	w.cub[5].m.ambient = 0.2;
	w.cub[5].m.specular = 0;
	w.cub[5].m.diffuse = 0.8;

	w.cub[6] = set_cube();
	w.cub[6].transform = matrix_mult(w.cub[6].transform, translation(2, -2, 0));
	w.cub[6].transform = matrix_mult(w.cub[6].transform, rotation_x(-0.7854));
	w.cub[6].transform = matrix_mult(w.cub[6].transform, rotation_y(3.927));
	w.cub[6].m.pattern = 1;
	w.cub[6].m.p = pattern;
	w.cub[6].m.p.transform = identity_matrix();
	w.cub[6].m.pattern_at = &pattern_at_cube;
	w.cub[6].m.ambient = 0.2;
	w.cub[6].m.specular = 0;
	w.cub[6].m.diffuse = 0.8;

	w.cub[7] = set_cube();
	w.cub[7].transform = matrix_mult(w.cub[7].transform, translation(6, -2, 0));
	w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_x(-0.7854));
	w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_y(5.4978));
	w.cub[7].m.pattern = 1;
	w.cub[7].m.p = pattern;
	w.cub[7].m.p.transform = identity_matrix();
	w.cub[7].m.pattern_at = &pattern_at_cube;
	w.cub[7].m.ambient = 0.2;
	w.cub[7].m.specular = 0;
	w.cub[7].m.diffuse = 0.8;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(0, 0, -20, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.cub_obj = 8;
	w.max_obj = 8;
	w.ar_count = 0;

	int i = 0;
	while (i < w.cub_obj)
	{
		push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.8); // 800 x 400
	c.transform = view_transform(set_v_p(0, 0, -20, 1), set_v_p(0, 0, 0, 1), set_v_p(0, 1, 0, 0));







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
