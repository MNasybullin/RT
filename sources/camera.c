/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:48 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/13 20:20:08 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	camera(double hsize, double vsize, double fov)
{
	t_camera	c;
	double		half_view;
	double		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.aliasing = 0;
	c.sepia = 0;
	c.fov = fov;
	c.transform = identity_matrix();
	half_view = SDL_tanf(c.fov / 2);
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

t_ray		ray_for_pixel(t_camera *camera, double px, double py)
{
	t_vec	pixel;
	t_vec	origin;
	t_vec	direction;

	pixel = matrix_mult_v_p(camera->transform,
	set_v_p((camera->half_width - ((px + 0.5) * camera->pixel_size)),
	(camera->half_height - ((py + 0.5) * camera->pixel_size)), -1, 1));
	origin = matrix_mult_v_p(camera->transform,
	set_v_p(0, 0, 0, 1));
	direction = normalize(sub(pixel, origin));
	return (set_ray(origin, direction));
}

t_color		sepia(t_color color)
{
	t_color	sepia;

	sepia.r = (0.396 * color.r) + (0.769 * color.g) + (0.189 * color.b);
	sepia.g = (0.349 * color.r) + (0.686 * color.g) + (0.168 * color.b);
	sepia.b = (0.272 * color.r) + (0.534 * color.g) + (0.131 * color.b);
	return (sepia);
}

void		screenshot_name(t_screenshot *s)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		s->file_name[i] = '0' + rand() % 72;
		i++;
	}
	s->file_name[5] = '.';
	s->file_name[6] = 'b';
	s->file_name[7] = 'm';
	s->file_name[8] = 'p';
	s->file_name[9] = '\0';
}

void		save_texture(SDL_Renderer *renderer, SDL_Texture *texture)
{
	t_screenshot	s;

	screenshot_name(&s);
	s.target = SDL_GetRenderTarget(renderer);
	if (SDL_SetRenderTarget(renderer, s.target) == -1)
		exit(EXIT_FAILURE);
	if (SDL_QueryTexture(texture, NULL, NULL, &s.width, &s.height) == -1)
		exit(EXIT_FAILURE);
	s.surface = SDL_CreateRGBSurface(0, s.width, s.height, 32, 0, 0, 0, 0);
	if (SDL_RenderReadPixels(renderer, NULL,
	s.surface->format->format, s.surface->pixels, s.surface->pitch) == -1)
		exit(EXIT_FAILURE);
	SDL_SaveBMP(s.surface, s.file_name);
	if (SDL_SaveBMP(s.surface, s.file_name) == -1)
		exit(EXIT_FAILURE);
	SDL_FreeSurface(s.surface);
	if (SDL_SetRenderTarget(renderer, s.target) == -1)
		exit(EXIT_FAILURE);
}
