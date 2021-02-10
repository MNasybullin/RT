/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:28:12 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 14:03:29 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	triangle_sides(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	init_4_tabs(&tab1, &tab2, &tab3, &tab4);
	if (len_tab(tab) == 9)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], ',');
		tab4 = ft_strsplit(tab[8], '}');
		if (flag == 5)
			w->trian[p->tri_i].p1 = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		else if (flag == 6)
			w->trian[p->tri_i].p2 = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		else if (flag == 7)
			w->trian[p->tri_i].p3 = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		free_split_tab4(&tab1, &tab2, &tab3, &tab4);
	}
}

void	tri_m_rotation(t_data *p, t_world *w, char **tab1, char **tab2)
{
	w->trian[p->tri_i].m.p.transform = matrix_mult(w->
	trian[p->tri_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
	w->trian[p->tri_i].m.p.transform = matrix_mult(w->
	trian[p->tri_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
}

void	texture_tri(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->trian[p->tri_i].m.tex = 1;
	}
}

void	tri_patterns_1(t_data *p, t_world *w)
{
	w->trian[p->tri_i].check.color_a = w->trian[p->tri_i].m.p.a;
	w->trian[p->tri_i].check.color_b = w->trian[p->tri_i].m.p.b;
	w->trian[p->tri_i].check.width = w->trian[p->tri_i].width;
	w->trian[p->tri_i].check.height = w->trian[p->tri_i].height;
	uv_checkers(w->trian[p->tri_i].check, &w->trian[p->tri_i].m.p);
	w->trian[p->tri_i].m.texturemap = texture_map(w->trian[p->tri_i].m.p,
		&planar_map);
}

void	tri_patterns(t_data *p, t_world *w)
{
	w->trian[p->tri_i].m.pattern_at = &pattern_at;
	if (w->trian[p->tri_i].pattern_type == 1)
		tri_patterns_1(p, w);
	else if (w->trian[p->tri_i].pattern_type == 2)
		stripe_pattern_shape(w->trian[p->tri_i].m.p.a,
		w->trian[p->tri_i].m.p.b, &w->trian[p->tri_i].m);
	else if (w->trian[p->tri_i].pattern_type == 3)
		gradient_pattern_shape(w->trian[p->tri_i].m.p.a,
		w->trian[p->tri_i].m.p.b, &w->trian[p->tri_i].m);
	else if (w->trian[p->tri_i].pattern_type == 4)
		ring_pattern_shape(w->trian[p->tri_i].m.p.a, w->trian[p->tri_i].m.p.b,
		&w->trian[p->tri_i].m);
	if (w->trian[p->tri_i].m.tex == 1)
	{
		w->trian[p->tri_i].m.texturemap = texture_map(w->trian[p->tri_i].m.p,
		&planar_map);
		w->trian[p->tri_i].m.texture = SDL_LoadBMP(w->trian[p->tri_i].texture);
	}
}
