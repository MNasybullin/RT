/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:14:58 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/05 19:15:05 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
