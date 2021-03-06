/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:44:11 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 14:48:07 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			aliasing(t_treads *treads, int x, int y, int remaining)
{
	t_color		col;
	int			i;
	double		u;
	double		v;

	i = 0;
	col = color(0, 0, 0);
	while (i < 8)
	{
		u = (x + drand48());
		v = (y + drand48());
		col = add_col(col, color_at(treads->world, ray_for_pixel(treads->camera,
		u, v), remaining));
		i++;
	}
	col = divide_col(col, 8);
	if (treads->camera->sepia == 1)
		col = sepia(col);
	treads->sdl->img[y * treads->camera->hsize + x] = col_to_int(col);
}

void			draw_ne_vlezlo(t_treads *treads, int x, int y, t_color *col)
{
	*col = color_at(treads->world, ray_for_pixel(treads->camera, x, y), 5);
	if (treads->camera->sepia == 1)
		*col = sepia(*col);
	treads->sdl->img[y * treads->camera->hsize + x] =
	col_to_int(*col);
}

int				draw(void *data)
{
	int			x;
	int			y;
	t_color		col;
	t_treads	*treads;

	treads = data;
	y = treads->start;
	while (y < treads->finish)
	{
		x = 0;
		while (x < treads->camera->hsize)
		{
			if (treads->camera->aliasing == 0)
			{
				draw_ne_vlezlo(treads, x, y, &col);
			}
			else
				aliasing(treads, x, y, 5);
			x++;
		}
		y++;
	}
	return (0);
}

void			render_join(t_sdl *sdl, SDL_Thread **threads)
{
	int			i;
	int			status;

	i = 0;
	while (i < THREADS)
	{
		SDL_WaitThread(threads[i], NULL);
		SDL_UpdateTexture(sdl->text, NULL, sdl->img, sizeof(int) * WIN_W);
		SDL_RenderClear(sdl->ren);
		SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
		SDL_RenderPresent(sdl->ren);
		i++;
	}
}

void			render(t_sdl *sdl, t_camera camera, t_world world)
{
	SDL_Thread	*threads[THREADS];
	t_treads	htreads[THREADS];
	int			i;

	i = 0;
	if (check_transform_matrix(&camera.transform, &camera.transform, 0) == 1)
		exit(-1);
	while (i < THREADS)
	{
		htreads[i].camera = &camera;
		htreads[i].sdl = sdl;
		htreads[i].world = &world;
		htreads[i].start = i * (camera.hsize / THREADS);
		htreads[i].finish = (i + 1) * (camera.hsize / THREADS);
		threads[i] = SDL_CreateThread(draw, NULL, htreads + i);
		i++;
	}
	render_join(sdl, threads);
}
