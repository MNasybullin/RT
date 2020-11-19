/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:32:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/11/19 19:12:54 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_col(t_color a1, t_color a2)
{
	a1.r += a2.r;
	a1.g += a2.g;
	a1.b += a2.b;
	return (a1);
}

t_color	sub_col(t_color a1, t_color a2)
{
	a1.r -= a2.r;
	a1.g -= a2.g;
	a1.b -= a2.b;
	return (a1);
}

t_color	mult_col(t_color a, double b)
{
	a.r *= b;
	a.g *= b;
	a.b *= b;
	return (a);
}

t_color	divide_col(t_color a, int b)
{
	a.r /= b;
	a.g /= b;
	a.b /= b;
	return (a);
}

t_color	hadamard_prod(t_color a1, t_color a2)
{
	a1.r *= a2.r;
	a1.g *= a2.g;
	a1.b *= a2.b;
	return (a1);
}

int	col_to_int(t_color c)
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

/*
int	c(double r, double g, double b)
{

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}
*/

t_color	get_color_tex(SDL_Surface *texture, int x, int y)
{
    Uint8 bpp = texture->format->BytesPerPixel;
	Uint32 pixel = *(Uint32 *)(((Uint8*)texture->pixels) + bpp * x + texture->pitch * y);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    //Uint8 a;
	//SDL_GetRGBA(pixel, &format, &r, &g, &b, &a);
	SDL_GetRGB(pixel, texture->format, &r, &g, &b); // из за тредов иногда проскакивают другие пиксели
	t_color c;
	double dr = r;
	double dg = g;
	double db = b;
	c = color(dr/255.0, dg/255.0, db/255.0);
	//printf("r = %i, g = %i, b = %i, x = %i, y = %i\n", r, g, b, x, y);
    return (c);
}
