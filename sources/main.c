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

void		ft_aquadisco(t_world *w)
{
	int		i;

	i = 0;
	while (i < w->max_obj)
	{
		w->obj_ar[i].m->color.r = rand() / (rand() + 0.2) + 0.1;
		w->obj_ar[i].m->color.g = rand() / (rand() + 0.2) + 0.1;
		w->obj_ar[i].m->color.b = rand() / (rand() + 0.2) + 0.1;
		i++;
	}
}

void		set_null_w(t_sdl *sdl, t_world *w)
{
	w->effective_render = 0;
	sdl->blur = 0;
	sdl->stereo = 0;
	sdl->cartoon = 0;
	w->aquadisco = -1;
}

void		run(t_sdl *sdl, t_world *w, t_data *p, char *av)
{
	while (SDL_PollEvent(&sdl->e) != 0)
		sdl_events(sdl, w, p, av);
	if (sdl->progress == 0)
	{
		render(sdl, w->c, *w);
		if (sdl->blur == 1)
			add_blurfilter(sdl);
		if (sdl->stereo == 1)
			add_stereofilter(sdl);
		if (sdl->cartoon == 1)
			cartoon_filter(sdl);
		SDL_SetWindowTitle(sdl->win, "RT");
		if (w->aquadisco == 1)
			ft_aquadisco(w);
		else
			++sdl->progress;
	}
}

int			main(int ac, char **av)
{
	t_sdl	sdl;
	t_world	w;
	t_data	p;

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
		run(&sdl, &w, &p, av[1]);
	quit(&sdl, EXIT_SUCCESS);
	return (0);
}
