/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:51:52 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 13:10:05 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	cone_patterns_1(t_data *p, t_world *w)
{
	w->cone[p->cone_i].check.color_a = w->cone[p->cone_i].m.p.a;
	w->cone[p->cone_i].check.color_b = w->cone[p->cone_i].m.p.b;
	w->cone[p->cone_i].check.width = w->cone[p->cone_i].width;
	w->cone[p->cone_i].check.height = w->cone[p->cone_i].height;
	uv_checkers(w->cone[p->cone_i].check, &w->cone[p->cone_i].m.p);
	w->cone[p->cone_i].m.texturemap = texture_map(w->cone[p->cone_i].m.p, &cylindrical_map);
}

void	cone_patterns(t_data *p, t_world *w)
{
	w->cone[p->cone_i].m.pattern_at = &pattern_at;
	if (w->cone[p->cone_i].pattern_type == 1)
		cone_patterns_1(p, w);
	else if (w->cone[p->cone_i].pattern_type == 2)
		stripe_pattern_shape(w->cone[p->cone_i].m.p.a,
		w->cone[p->cone_i].m.p.b, &w->cone[p->cone_i].m);
	else if (w->cone[p->cone_i].pattern_type == 3)
		gradient_pattern_shape(w->cone[p->cone_i].m.p.a,
		w->cone[p->cone_i].m.p.b, &w->cone[p->cone_i].m);
	else if (w->cone[p->cone_i].pattern_type == 4)
		ring_pattern_shape(w->cone[p->cone_i].m.p.a,
		w->cone[p->cone_i].m.p.b, &w->cone[p->cone_i].m);
	if (w->cone[p->cone_i].m.tex == 1)
	{
		w->cone[p->cone_i].m.texture =
		SDL_LoadBMP(w->cone[p->cone_i].texture);
		w->cone[p->cone_i].m.texturemap =
		texture_map(w->cone[p->cone_i].m.p, &cylindrical_map);
	}
}

void	pattern_type_cone(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[1], "checker")))
		w->cone[p->cone_i].pattern_type = 1;
	if (!(ft_strcmp(tab[1], "stripe")))
		w->cone[p->cone_i].pattern_type = 2;
	if (!(ft_strcmp(tab[1], "gradient")))
		w->cone[p->cone_i].pattern_type = 3;
	if (!(ft_strcmp(tab[1], "ring")))
		w->cone[p->cone_i].pattern_type = 4;
	if (!(ft_strcmp(tab[1], "1")))
		w->cone[p->cone_i].m.pattern = 1;
}
