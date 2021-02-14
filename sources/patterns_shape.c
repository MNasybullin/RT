/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:18:23 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 14:29:08 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			stripe_pattern_shape(t_color a, t_color b, t_material *m)
{
	m->p.a = a;
	m->p.b = b;
	/*m->p.transform = identity_matrix();*/
	m->pattern = 1;
	m->pattern_at = &stripe_at;
}

void			gradient_pattern_shape(t_color a, t_color b, t_material *m)
{
	m->p.a = a;
	m->p.b = b;
	/*m->p.transform = identity_matrix();*/
	m->pattern = 1;
	m->pattern_at = &gradient_at;
}

void			ring_pattern_shape(t_color a, t_color b, t_material *m)
{
	m->p.a = a;
	m->p.b = b;
	/*m->p.transform = identity_matrix();*/
	m->pattern = 1;
	m->pattern_at = &ring_at;
}

void			checker_pattern_shape(t_color a, t_color b, t_material *m)
{
	m->p.a = a;
	m->p.b = b;
	/*m->p.transform = identity_matrix();*/
	m->pattern = 1;
	m->pattern_at = &checker_at;
}
