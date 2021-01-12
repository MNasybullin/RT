/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_patterns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:52:03 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 14:16:43 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*void	init_cyl(t_data *p, t_world *w, char **tab)
{
	w->cyl[p->cyl_i] = set_cylinder();
	tab = NULL;
	w->cyl[p->cyl_i].pattern = 0;
	w->cyl[p->cyl_i].is_tex = 0;
	w->cyl[p->cyl_i].pattern_type = 0;
	w->cyl[p->cyl_i].m.tex = 0;
}*/

void	pattern_color_cyl(t_data *p, t_world *w, char **tab, int flag)
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
			w->cyl[p->cyl_i].m.p.a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2)
			w->cyl[p->cyl_i].m.p.b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	texture_cyl(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cyl[p->cyl_i].m.tex = 1;
	}
}

void	cyl_patterns_1(t_data *p, t_world *w, t_uv_check check)
{
	check.color_a = w->cyl[p->cyl_i].m.p.a;
	check.color_b = w->cyl[p->cyl_i].m.p.b;
	check.width = w->cyl[p->cyl_i].width;
	check.height = w->cyl[p->cyl_i].height;
	uv_checkers(check, &w->cyl[p->cyl_i].m.p);
	w->cyl[p->cyl_i].m.texturemap = texture_map(w->cyl[p->cyl_i].m.p,
		&cylindrical_map);
}

void	cyl_patterns(t_data *p, t_world *w)
{
	t_uv_check	check;

	check.width = 0;
	w->cyl[p->cyl_i].m.pattern_at = &pattern_at;
	if (w->cyl[p->cyl_i].pattern_type == 1)
		cyl_patterns_1(p, w, check);
	else if (w->cyl[p->cyl_i].pattern_type == 2)
		stripe_pattern_shape(w->cyl[p->cyl_i].m.p.a, w->cyl[p->cyl_i].m.p.b,
		&w->cyl[p->cyl_i].m);
	else if (w->cyl[p->cyl_i].pattern_type == 3)
		gradient_pattern_shape(w->cyl[p->cyl_i].m.p.a, w->cyl[p->cyl_i].m.p.b,
		&w->cyl[p->cyl_i].m);
	else if (w->cyl[p->cyl_i].pattern_type == 4)
		ring_pattern_shape(w->cyl[p->cyl_i].m.p.a, w->cyl[p->cyl_i].m.p.b,
		&w->cyl[p->cyl_i].m);
	if (w->cyl[p->cyl_i].m.tex == 1)
	{
		w->cyl[p->cyl_i].m.texturemap = texture_map(w->cyl[p->cyl_i].m.p,
		&cylindrical_map);
		w->cyl[p->cyl_i].m.texture = SDL_LoadBMP(w->cyl[p->cyl_i].texture);
	}
}
