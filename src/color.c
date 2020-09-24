/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:32:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/21 19:55:35 by sdiego           ###   ########.fr       */
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
	t_color	b;

	b.r = a1.r + a2.r;
	b.g = a1.g + a2.g;
	b.b = a1.b + a2.b;
	return (b);
}

t_color	sub_col(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r - a2.r;
	b.g = a1.g - a2.g;
	b.b = a1.b - a2.b;
	return (b);
}

t_color	mult_col(t_color a, double b)
{
	a.r = a.r * b;
	a.g = a.g * b;
	a.b = a.b * b;
	return (a);
}

t_color	divide_col(t_color a, int b)
{
	a.r = a.r / b;
	a.g = a.g / b;
	a.b = a.b / b;
	return (a);
}

t_color	hadamard_prod(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r * a2.r;
	b.g = a1.g * a2.g;
	b.b = a1.b * a2.b;
	return (b);
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
