/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: out-nasybullin-mr <out-nasybullin-mr@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/02 22:38:40 by out-nasybul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

int		key_press(t_sdl *sdl, t_camera *camera, t_world *w)
{
	if (KEY == SDLK_ESCAPE)
		sdl->run = 1;
	else if (KEY == SDLK_F12)
		save_texture(sdl->ren, sdl->text);
	else if (KEY == SDLK_1 || KEY == SDLK_2 || KEY == SDLK_3)
	{
		if (KEY == SDLK_1)
			camera->aliasing = camera->aliasing == 0 ? 1 : 0;
		else if (KEY == SDLK_2)
			camera->sepia = camera->sepia == 0 ? 1 : 0;
		else if (KEY == SDLK_3)
			w->effective_render = w->effective_render == 0 ? 1 : 0;
		sdl->progress = 0;
	}
	if (w->effective_render == 1)
		check_camera_position(sdl, w);
	if (sdl->progress == 0)
		SDL_SetWindowTitle(sdl->win, "RT - Rendering in progress ...");
	return (0);
}

void	init_sdl_error(void)
{
	write(1, "SDL Init Error\n", 15);
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

int		main(int ac, char **av)
{
	t_sdl		sdl;
	t_world		w;
	t_data		p;

	if (ac == 2)
	{
		init(&sdl);
		sdl.run = 0;
		p.obj_n = 0;
		p.fd = 0;
		if ((check_format(av[1])) != 1)
		{
			ft_putendl("\nWrong Format or invalid file\n");
            return (0);
		}
		read_file(av[1], &p, &w);
	}
	else
	{
		ft_putendl("\nUsage: ./RT <file.yml>\n");
		return (0);
	}
	sdl.progress = 0;
	w.s_obj = p.sp_num;
	w.pl_obj = p.pl_num;
	w.cone_obj = p.cone_num;
	w.cyl_obj = p.cyl_num;
	w.cub_obj = p.cube_num;
	w.trian_obj = p.tri_num;
	w.max_obj = p.obj_n;
	w.ar_count = 0;
	pushing_objects(&p, &w);
	
// Добавть камеру в парсер 
	// t_camera c;
	// c.from_x = 1;
	// c.from_y = 2;
	// c.from_z = -10;

	// c.to_x = 0;
	// c.to_y = 1.1;
	// c.to_z = 0;

	// c.up_x = 0;
	// c.up_y = 1;
	// c.up_z = 0;

	w.effective_render = 0;
	SDL_SetWindowTitle(sdl.win, "RT - Rendering in progress ...");
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			if (sdl.e.type == SDL_KEYDOWN)
				key_press(&sdl, &w.c, &w);
		}
		if (sdl.progress == 0)
		{
			render(&sdl, w.c, w);
			SDL_SetWindowTitle(sdl.win, "RT");
			sdl.progress++;
		}
	}
	quit(&sdl, EXIT_SUCCESS);
	return (0);
}
