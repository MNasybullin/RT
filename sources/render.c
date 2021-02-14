/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:44:11 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 12:37:56 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			aliasing(t_treads *treads, int x, int y, int remaining)
{
	t_color	col;
	int		i;
	double	u;
	double	v;

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

void			draw(t_treads *treads)
{
	int		x;
	int		y;
	t_color	col;

	y = treads->start;
	while (y < treads->finish)
	{
		x = 0;
		while (x < treads->camera->hsize)
		{
			if (treads->camera->aliasing == 0)
			{
				col = color_at(treads->world, ray_for_pixel(treads->camera, x,
				y), 5);
				if (treads->camera->sepia == 1)
					col = sepia(col);
				treads->sdl->img[y * treads->camera->hsize + x] =
				col_to_int(col);
			}
			else
				aliasing(treads, x, y, 5);
			x++;
		}
		y++;
	}
}

pthread_attr_t	stack_size(void)
{
	pthread_attr_t	thread_attr;

	if (pthread_attr_init(&thread_attr) != 0)
	{
		write(1, "Cannot create thread\n", 21);
		exit(EXIT_FAILURE);
	}
	if (pthread_attr_setstacksize(&thread_attr, 5 * 1024 * 1024) != 0)
	{
		write(1, "Cannot create thread\n", 21);
		exit(EXIT_FAILURE);
	}
	return (thread_attr);
}

void			render_join(t_sdl *sdl, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(threads[i], NULL) ||
		SDL_UpdateTexture(sdl->text, NULL, sdl->img,
		sizeof(int) * WIN_W) == -1 ||
		SDL_RenderClear(sdl->ren) == -1 || SDL_RenderCopy(sdl->ren,
		sdl->text, NULL, NULL) == -1)
		{
			write(1, "error threads or sdl update render error\n", 41);
			exit(-1);
		}
		SDL_RenderPresent(sdl->ren);
		i++;
	}
}

void			render(t_sdl *sdl, t_camera camera, t_world world)
{
	pthread_t		threads[THREADS];
	t_treads		htreads[THREADS];
	pthread_attr_t	thread_attr;
	int				i;

	i = 0;
	thread_attr = stack_size();
	if (check_transform_matrix(&camera.transform, &camera.transform, 0) == 1)
	{
		printf("CAMERA\n\n\n\n\n");
		exit(-1);	
	}
	while (i < THREADS)
	{
		htreads[i].camera = &camera;
		htreads[i].sdl = sdl;
		htreads[i].world = &world;
		htreads[i].start = i * (camera.hsize / THREADS);
		htreads[i].finish = (i + 1) * (camera.hsize / THREADS);
		if (pthread_create(&threads[i], &thread_attr, (void *)draw,
		(void *)&htreads[i]) != 0)
		{
			write(1, "error threads create\n", 21);
			exit(-1);
		}
		i++;
	}
	render_join(sdl, threads);
}
