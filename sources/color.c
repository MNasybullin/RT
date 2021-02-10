/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:32:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/05 19:14:56 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	hadamard_prod(t_color a1, t_color a2)
{
	a1.r *= a2.r;
	a1.g *= a2.g;
	a1.b *= a2.b;
	return (a1);
}

int		col_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = c.r * 255;
	g = c.g * 255;
	b = c.b * 255;
	r > 255 ? r = 255 : r;
	g > 255 ? g = 255 : g;
	b > 255 ? b = 255 : b;
	r < 0 ? r = 0 : r;
	g < 0 ? g = 0 : g;
	b < 0 ? b = 0 : b;
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

t_color	get_color_tex(SDL_Surface *texture, int x, int y)
{
	Uint8	bpp;
	Uint32	pixel;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	bpp = texture->format->BytesPerPixel;
	pixel = *(Uint32 *)(((Uint8*)texture->pixels) + bpp *
	x + texture->pitch * y);
	SDL_GetRGB(pixel, texture->format, &r, &g, &b);
	return (color((double)r / 255.0, (double)g / 255.0, (double)b / 255.0));
}
