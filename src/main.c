/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/14 18:09:56 by sdiego           ###   ########.fr       */
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
	if (check_transform_matrix(w.cub[i].transform, w.cub[i].m.p.transform, w.cub[i].m.pattern) == EXIT_FAILURE)
		exit(-1); // нужно сделать правильный выход из программы
	push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
	i++;
}

t_camera c = camera(WIN_W, WIN_H, 0.785);
c.transform = view_transform(set_v_p(8, 6, -8, 1), set_v_p(0, 3, 0, 1), set_v_p(0, 1, 0, 0));






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
