/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:28:00 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/01 15:42:59 by mgalt            ###   ########.fr       */
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


int		main(int ac, char **av)
{
	t_sdl		sdl;
	t_world		w;
	t_data		p;

	if (ac == 2)
	{
		if (init(&sdl) != 0)
			quit(&sdl);
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
	printf("\n\nCUBE TEXTURE: %s\n\n\n", w.cub[0].right);
	printf("\n\nCUBE TEX: %d\n\n\n", w.cub[0].m.tex);
	printf("\n\nCUBE pat: %d\n\n\n", w.cub[0].m.pattern);
	//printf("OBJ PARAMETERS: (%f, %f, %f); radius %f; shininess %f\n", w.s[0].m.color.r, w.s[0].m.color.g, w.s[0].m.color.b, w.s[0].r, w.s[0].m.shininess);
	//printf("CAMERA PARAMETERS: %d, %d, %f\n", w.c.hsize, w.c.vsize, w.c.fov);
	//printf("LIGHT PARAMETERS:\n---\n%f %f %f %f %f %f %f\n", p.h[0].r, p.h[0].g, p.h[0].bl, p.h[0].a, p.h[0].b, p.h[0].c, p.h[0].w);
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			if (sdl.e.type == SDL_KEYDOWN)
				key_press(&sdl, &w.c);
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
			render(&sdl, w.c, w);
			write(1, "Render complete!\n", 17);
			sdl.progress++;
		}
	}
	quit(&sdl);
	return(0);
}
