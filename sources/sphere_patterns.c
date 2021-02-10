/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_patterns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:54:47 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 13:55:59 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	texture_sp(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->s[p->sp_i].m.tex = 1;
	}
}

void	sphere_patterns_1(t_data *p, t_world *w)
{
	w->s[p->sp_i].check.color_a = w->s[p->sp_i].m.p.a;
	w->s[p->sp_i].check.color_b = w->s[p->sp_i].m.p.b;
	w->s[p->sp_i].check.width = w->s[p->sp_i].width;
	w->s[p->sp_i].check.height = w->s[p->sp_i].height;
	uv_checkers(w->s[p->sp_i].check, &w->s[p->sp_i].m.p);
	w->s[p->sp_i].m.texturemap = texture_map(w->s[p->sp_i].m.p,
		&spherical_map);
}

void	sphere_patterns(t_data *p, t_world *w)
{
	w->s[p->sp_i].m.pattern_at = &pattern_at;
	if (w->s[p->sp_i].pattern_type == 1)
		sphere_patterns_1(p, w);
	else if (w->s[p->sp_i].pattern_type == 2)
		stripe_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	else if (w->s[p->sp_i].pattern_type == 3)
		gradient_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	else if (w->s[p->sp_i].pattern_type == 4)
		ring_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	if (w->s[p->sp_i].m.tex == 1)
	{
		w->s[p->sp_i].m.texture = SDL_LoadBMP(w->s[p->sp_i].texture);
		w->s[p->sp_i].m.texturemap = texture_map(w->s[p->sp_i].m.p,
		&spherical_map);
	}
	if ((w->s[p->sp_i].pattern_type < 1 || w->s[p->sp_i].pattern_type > 4)
	&& w->s[p->sp_i].m.tex != 1)
		w->s[p->sp_i].m.pattern = 0;
}

void	pattern_type_sphere(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[1], "checker")))
		w->s[p->sp_i].pattern_type = 1;
	if (!(ft_strcmp(tab[1], "stripe")))
		w->s[p->sp_i].pattern_type = 2;
	if (!(ft_strcmp(tab[1], "gradient")))
		w->s[p->sp_i].pattern_type = 3;
	if (!(ft_strcmp(tab[1], "ring")))
		w->s[p->sp_i].pattern_type = 4;
	if (!(ft_strcmp(tab[1], "1")))
		w->s[p->sp_i].m.pattern = 1;
}
