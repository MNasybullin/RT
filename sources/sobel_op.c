/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sobel_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:52:59 by rnarbo            #+#    #+#             */
/*   Updated: 2021/02/14 13:48:06 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_pixel(int *sdl, int i, int j)
{
	if (i < 0 || j < 0 || i >= WIN_W || j >= WIN_H)
		return (0);
	return (sdl[i + WIN_W * j] & 0xff);
}

int		get_sobel_pix(int *sdl, int i, int j)
{
	int pixel_x;
	int pixel_y;
	int ret;

	pixel_x =
		(-get_pixel(sdl, i - 1, j - 1) + get_pixel(sdl, i + 1, j - 1)) +
		(-2 * get_pixel(sdl, i - 1, j) + 2 * get_pixel(sdl, i + 1, j)) +
		(-1 * get_pixel(sdl, i - 1, j + 1) + get_pixel(sdl, i + 1, j + 1));
	pixel_y =
		(-get_pixel(sdl, i - 1, j - 1) - 2 * get_pixel(sdl, i, j - 1)) -
		get_pixel(sdl, i + 1, j - 1) + (get_pixel(sdl, i - 1, j + 1) +
		2 * get_pixel(sdl, i, j + 1)) + get_pixel(sdl, i + 1, j + 1);
	ret = (int)sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));
	ret += (ret << 8) + (ret << 16);
	return (ret);
}

int*	ft_gray(t_sdl *sdl)
{
	int i;
	int deff;
	t_argb	argb;
	int	*new;

	new = malloc(sizeof(int) * WIN_H * WIN_W);
	i = 0;
	while (i < WIN_H * WIN_W - 1)
	{
		argb.color = sdl->img[i];
		deff = (argb.parts.r + argb.parts.g + argb.parts.b) / 3;
		argb.parts.r = deff;
		argb.parts.g = deff;
		argb.parts.b = deff;
		new[i] = argb.color;
		i++;
	}
	return(new);
}

int*	sobel_op(t_sdl *sdl)
{
	int i;
	int j;
	int	*new;
	int *grey;

	new = malloc(sizeof(int) * WIN_H * WIN_W);
	grey = ft_gray(sdl);
	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			new[i + j * WIN_W] = get_sobel_pix(grey, i, j);
			i++;
		}
		j++;
	}
	free(grey);
	return(new);
}

void	cartoon_filter(t_sdl *sdl)
{
	int i;
	int	*new;

	new = sobel_op(sdl);
	i = 0;
	while (i < WIN_H * WIN_W)
	{
		sdl->img[i] = (new[i] ^ 0xffffff) & sdl->img[i];
		i++;
	}
	SDL_UpdateTexture(sdl->text, NULL, sdl->img, sizeof(int) * WIN_W);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
	free(new);
}
