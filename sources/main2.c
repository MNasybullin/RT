/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 13:49:33 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_blurfilter(t_sdl *sdl)
{
	t_argb	argb;
	t_argb	argb2;
	t_argb	argb3;
	int		i;

	i = 0;
	while (i < (WIN_H * WIN_W) - 1)
	{
		argb.color = sdl->img[i];
		argb2.color = sdl->img[i + 1];
		argb3.color = sdl->img[i + 2];
		argb3.parts.r = (argb2.parts.r + argb.parts.r + argb3.parts.r) / 3;
		argb3.parts.g = (argb2.parts.g + argb.parts.g + argb3.parts.g) / 3;
		argb3.parts.b = (argb2.parts.b + argb.parts.b + argb3.parts.b) / 3;
		sdl->img[i + 2] = argb3.color;
		i++;
	}
	SDL_UpdateTexture(sdl->text, NULL, sdl->img, sizeof(int) * WIN_W);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}

void	keys(t_sdl *sdl, t_world *w, t_data *p, char *path)
{
	if (KEY == SDLK_ESCAPE)
		sdl->run = 1;
	else if (KEY == SDLK_F12)
		save_texture(sdl->ren, sdl->text);
	else if (KEY == SDLK_1 || KEY == SDLK_2 || KEY == SDLK_3 || KEY == SDLK_o)
	{
		if (KEY == SDLK_1)
			w->c.aliasing = w->c.aliasing == 0 ? 1 : 0;
		else if (KEY == SDLK_2)
			w->c.sepia = w->c.sepia == 0 ? 1 : 0;
		else if (KEY == SDLK_3)
			w->effective_render = w->effective_render == 0 ? 1 : 0;
		else if (KEY == SDLK_o)
			w->aquadisco *= -1;
		sdl->progress = 0;
	}
	else if (KEY == SDLK_n && !(sdl->progress = 0))
		read_config(sdl, w, p, path);
}

void	key_press(t_sdl *sdl, t_world *w, t_data *p, char *path)
{
	keys(sdl, w, p, path);
	if (KEY == SDLK_4)
	{
		sdl->blur = sdl->blur == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	if (KEY == SDLK_5)
	{
		sdl->stereo = sdl->stereo == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	if (KEY == SDLK_6)
	{
		sdl->cartoon = sdl->cartoon == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	if (w->effective_render == 1)
		check_camera_position(sdl, w);
	if (sdl->progress == 0)
		SDL_SetWindowTitle(sdl->win, "RT - Rendering in progress ...");
}

void	init_sdl_error(void)
{
	write(2, "SDL Init Error\n", 15);
	exit(EXIT_FAILURE);
}

void	init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		init_sdl_error();
	if ((sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)) == NULL)
		init_sdl_error();
	if ((sdl->icon = SDL_LoadBMP("icon.bmp")) == NULL)
		init_sdl_error();
	SDL_SetWindowIcon(sdl->win, sdl->icon);
	if ((sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0)) == NULL)
		init_sdl_error();
	if ((sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H)) == NULL)
		init_sdl_error();
	if ((sdl->img = malloc(WIN_W * WIN_H * sizeof(int))) == NULL)
		init_sdl_error();
}
