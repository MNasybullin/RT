/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:51:52 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/15 16:52:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	cone_patterns_1(t_data *p, t_world *w, t_uv_check check)
{
	check.color_a = w->cone[p->cone_i].color_a;
	check.color_b = w->cone[p->cone_i].color_b;
	check.width = w->cone[p->cone_i].width;
	check.height = w->cone[p->cone_i].height;
	uv_checkers(check, &w->cone[p->cone_i].m.p);
}

void	cone_patterns(t_data *p, t_world *w)
{
	t_uv_check	check;

	check.width = 0;
	w->cone[p->cone_i].m.pattern_at = &pattern_at;
	if (w->cone[p->cone_i].pattern_type == 1)
		cone_patterns_1(p, w, check);
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
