/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 13:49:33 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	quit(t_sdl *sdl, int error)
{
	if (sdl->text != NULL)
		SDL_DestroyTexture(sdl->text);
	sdl->text = NULL;
	if (sdl->img != NULL)
		free(sdl->img);
	SDL_FreeSurface(sdl->icon);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
	exit(error);
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

void		add_stereofilter(t_sdl *sdl)
{
	t_sdl	*sdl2;
	t_argb	argb;
	t_argb	argb2;
	int		i;

	i = 0;
	sdl2 = sdl;
	while (i < (WIN_H * WIN_W) - 1)
	{
		argb.color = sdl->img[i];
		argb2.color = sdl2->img[i + 10];
		argb.parts.g = 0;
		argb.parts.g = argb2.parts.g;
		sdl->img[i] = argb.color;
		i++;
	}
	SDL_UpdateTexture(sdl->text, NULL, sdl->img, sizeof(int) * WIN_W);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}

void	ft_aquadisco(t_world *w)
{
	int	i;

	i = 0;
	while (i < w->max_obj)
	{
		w->obj_ar[i].m->color.r = rand() / (rand() + 0.2) + 0.1;
		w->obj_ar[i].m->color.g = rand() / (rand() + 0.2) + 0.1;
		w->obj_ar[i].m->color.b = rand() / (rand() + 0.2) + 0.1;
		i++;
	}
}

void	set_null_w(t_sdl *sdl, t_world *w)
{
	w->effective_render = 0;
	sdl->blur = 0;
	sdl->stereo = 0;
	sdl->cartoon = 0;
	w->aquadisco = -1;
}

int		main(int ac, char **av)
{
	t_sdl		sdl;
	t_world		w;
	t_data		p;

	if (ac == 2)
	{
		init(&sdl);
		read_config(&sdl, &w, &p, av[1]);
	}
	else
	{
		ft_putendl("\nUsage: ./RT <file.yml>\n");
		return (1);
	}
	set_null_w(&sdl, &w);
	SDL_SetWindowTitle(sdl.win, "RT - Rendering in progress ...");
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			if (sdl.e.type == SDL_KEYDOWN)
				key_press(&sdl, &w, &p, av[1]);
		}
		if (sdl.progress == 0)
		{
			render(&sdl, w.c, w);
			if (sdl.blur == 1)
				add_blurfilter(&sdl);
			if (sdl.stereo == 1)
				add_stereofilter(&sdl);
			if (sdl.cartoon == 1)
				cartoon_filter(&sdl);
			SDL_SetWindowTitle(sdl.win, "RT");
			if (w.aquadisco == 1)
				ft_aquadisco(&w);
			else
				++sdl.progress;
		}
	}
	quit(&sdl, EXIT_SUCCESS);
	return (0);
}
