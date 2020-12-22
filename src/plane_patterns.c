/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 20:45:42 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/17 20:48:13 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	plane_patterns_1(t_data *p, t_world *w, t_uv_check check)
{
	check.color_a = w->pl[p->pl_i].color_a;
	check.color_b = w->pl[p->pl_i].color_b;
	check.width = w->pl[p->pl_i].width;
	check.height = w->pl[p->pl_i].height;
	uv_checkers(check, &w->pl[p->pl_i].m.p);
}

void	plane_patterns(t_data *p, t_world *w)
{
	t_uv_check	check;

	check.width = 0;
	w->pl[p->pl_i].m.pattern_at = &pattern_at;
	if (w->pl[p->pl_i].pattern_type == 1)
		plane_patterns_1(p, w, check);
	else if (w->pl[p->pl_i].pattern_type == 2)
		stripe_pattern_shape(w->pl[p->pl_i].m.p.a, w->pl[p->pl_i].m.p.b,
		&w->pl[p->pl_i].m);
	else if (w->pl[p->pl_i].pattern_type == 3)
		gradient_pattern_shape(w->pl[p->pl_i].m.p.a, w->pl[p->pl_i].m.p.b,
		&w->pl[p->pl_i].m);
	else if (w->pl[p->pl_i].pattern_type == 4)
		ring_pattern_shape(w->pl[p->pl_i].m.p.a, w->pl[p->pl_i].m.p.b,
		&w->pl[p->pl_i].m);
	if (w->pl[p->pl_i].m.tex == 1)
	{
		w->pl[p->pl_i].m.texturemap = texture_map(w->pl[p->pl_i].m.p,
		&planar_map);
		w->pl[p->pl_i].m.texture = SDL_LoadBMP(w->pl[p->pl_i].texture);
	}
}

void	pattern_color_pl(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	if (len_tab(tab) == 7)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], '}');
		if (flag == 1)
			w->pl[p->pl_i].m.p.a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2)
			w->pl[p->pl_i].m.p.b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->pl[p->pl_i].color_a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->pl[p->pl_i].color_b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	texture_plane(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->pl[p->pl_i].m.tex = 1;
	}
}
