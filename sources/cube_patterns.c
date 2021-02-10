/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:55:40 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/15 17:44:29 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cube(t_data *p, t_world *w, char **tab)
{
	w->cub[p->cube_i] = set_cube();
	w->cub[p->cube_i].pattern = 0;
	w->cub[p->cube_i].tex_num = 0;
	w->cub[p->cube_i].pattern_type = 0;
	tab = NULL;
}

void	texture_cube(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cub[p->cube_i].m.tex = 1;
	}
}

void	cube_patterns(t_data *p, t_world *w)
{
	w->cub[p->cube_i].m.pattern = 1;
	if (w->cub[p->cube_i].pattern_type == 1)
		checker_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b,
		&w->cub[p->cube_i].m);
	else if (w->cub[p->cube_i].pattern_type == 2)
		stripe_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b,
		&w->cub[p->cube_i].m);
	else if (w->cub[p->cube_i].pattern_type == 3)
		gradient_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b,
		&w->cub[p->cube_i].m);
	else if (w->cub[p->cube_i].pattern_type == 4)
		ring_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b,
		&w->cub[p->cube_i].m);
	else
		exit(-1);
}

void	pattern_color_cube(t_data *p, t_world *w, char **tab, int flag)
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
			w->cub[p->cube_i].m.p.a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2)
			w->cub[p->cube_i].m.p.b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}
