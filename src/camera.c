/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:48 by sdiego            #+#    #+#             */
/*   Updated: 2020/11/19 19:13:18 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_camera    camera(double  hsize, double vsize, double fov)
{
    t_camera    c;
    double       half_view;
    double       aspect;

    c.hsize = hsize;
    c.vsize = vsize;
    c.aliasing = 0;
    c.sepia = 0;
    c.fov = fov;
    c.transform = identity_matrix();
    half_view = tanf(c.fov / 2);
    aspect = hsize / vsize;
    if (aspect >= 1)
    {
        c.half_width = half_view;
        c.half_height = half_view / aspect;
    }
    else
    {
        c.half_width = half_view * aspect;
        c.half_height = half_view;
    }
    c.pixel_size = (c.half_width * 2) / c.hsize;
    return (c);
}

t_ray   ray_for_pixel(t_camera *camera, double px, double py)
{
    double   xoffset;
    double   yoffset;
    double   world_x;
    double   wolrd_y;
    t_vec   pixel;
    t_vec   origin;
    t_vec   direction;

    xoffset = (px + 0.5) * camera->pixel_size;
    yoffset = (py + 0.5) * camera->pixel_size;
    world_x = camera->half_width - xoffset;
    wolrd_y = camera->half_height - yoffset;

    pixel = matrix_mult_v_p(matrix_inverse(camera->transform), set_v_p(world_x, wolrd_y, -1 , 1));
    origin = matrix_mult_v_p(matrix_inverse(camera->transform), set_v_p(0, 0, 0, 1));
    direction = normalize(sub(pixel, origin));

    return (set_ray(origin, direction));
}

#include <pthread.h>
#define THREADS 400

typedef struct		s_treads
{
	t_sdl            *sdl;
    t_camera       *camera;
    t_world         *world;
    int				start;
	int				finish;
}					t_treads;

t_color sepia(t_color color)
{
    t_color sepia;

    sepia.r = (0.396 * color.r) + (0.769 * color.g) + (0.189 * color.b);
    sepia.g = (0.349 * color.r) + (0.686 * color.g) + (0.168 * color.b);
    sepia.b = (0.272 * color.r) + (0.534 * color.g) + (0.131 * color.b);
    return (sepia);
}

void    aliasing(t_treads *treads, int x, int y, int remaining)
{
    t_ray   r;
    t_color col;
    int i;
    double u;
    double v;

    i = 0;
    col = color(0, 0, 0);
    while (i < 6)
    {
        u = (x + drand48());
        v = (y + drand48());
        r = ray_for_pixel(treads->camera, u, v);
        col = add_col(col, color_at(treads->world, r, remaining));
        i++;
    }
    col = divide_col(col, 6);
    if (treads->camera->sepia == 1)
        col = sepia(col);
    treads->sdl->img[y * treads->camera->hsize + x] = col_to_int(col);
}

void    draw(t_treads *treads)
{
    int     x;
    int     y;
    t_ray   r;
    t_color col;
    int remaining = 5; // повторений рекурсии в отражении

    y = treads->start;
    while (y < treads->finish)
    {
        x = 0;
        while (x < treads->camera->hsize)
        {
            if (treads->camera->aliasing == 0)
            {
                r = ray_for_pixel(treads->camera, x, y);
                col = color_at(treads->world, r, remaining);
                if (treads->camera->sepia == 1)
                    col = sepia(col);
                treads->sdl->img[y * treads->camera->hsize + x] = col_to_int(col);
            }
            else
                aliasing(treads, x, y, remaining);
            x++;
        }
        y++;
    }
}

void save_texture(SDL_Renderer* renderer, SDL_Texture* texture)
{
    int		i;
	char	file_name[10];

	i = 0;
	while (i < 5)
	{
		file_name[i] = '0' + rand()%72;
		i++;
	}
	file_name[5] = '.';
	file_name[6] = 'b';
	file_name[7] = 'm';
	file_name[8] = 'p';
    file_name[9] = '\0';
	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, texture);
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
	SDL_SaveBMP(surface, file_name);
	SDL_FreeSurface(surface);
	SDL_SetRenderTarget(renderer, target);
}

pthread_attr_t stack_size(void)
{
    pthread_attr_t thread_attr;
    int err;

    err = pthread_attr_init(&thread_attr);
    if(err != 0)
    {
        printf("Cannot create thread attribute: %i\n", err);
        exit(-1);
    }
    // Устанавливаем минимальный размер стека для потока (в байтах)
    err = pthread_attr_setstacksize(&thread_attr, 5*1024*1024);
    if(err != 0)
    {
        printf("Cannot create thread attribute: %i\n", err);
        exit(-1);
    }

    return (thread_attr);
}

void    render(t_sdl *sdl, t_camera camera, t_world world)
{
    pthread_t	threads[THREADS];
	t_treads    htreads[THREADS];
	int i = 0;

    pthread_attr_t thread_attr;

    thread_attr = stack_size();
    if (check_transform_matrix(camera.transform, camera.transform, 0) == EXIT_FAILURE)
        exit(-1);
    while (i < THREADS)
	{
		htreads[i].camera = &camera;
        htreads[i].sdl = sdl;
        htreads[i].world = &world;
		htreads[i].start = i * (camera.hsize / THREADS);
		htreads[i].finish = (i + 1) * (camera.hsize / THREADS);
		if (pthread_create(&threads[i], &thread_attr, (void *)draw, (void *)&htreads[i]) != 0)
        {
            printf("error threads\n");
            exit(-1);
        }
		i++;
	}
    i = 0;
	while (i < THREADS)
    {
		if (pthread_join(threads[i], NULL))
		{
            printf("error threads\n");
            exit(-1);
        }

        SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_W * (sizeof(int)));
	    SDL_RenderClear(sdl->ren);
	    SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	    SDL_RenderPresent(sdl->ren);
        i++;
    }
}

/*
void    render(t_sdl *sdl, t_camera camera, t_world world)
{
    int     x;
    int     y;
    t_ray   r;
    t_color col;

    int remaining = 5; // повторений рекурсии в отражении

    y = 0;
    while (y < camera.vsize)
    {
        x = 0;
        while (x < camera.hsize)
        {
            r = ray_for_pixel(camera, x, y);
            col = color_at(world, r, remaining);
            sdl->img[y * camera.hsize + x] = col_to_int(col);
            x++;
        }

		SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_W * (sizeof(int)));
		SDL_RenderClear(sdl->ren);
		SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
		SDL_RenderPresent(sdl->ren);

        y++;
    }
}
*/
