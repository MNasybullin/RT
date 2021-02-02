/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:50:35 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/17 18:55:27 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	cyl_crutch_3(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	tab1 = ft_strsplit(tab[2], ',');
	tab2 = ft_strsplit(tab[4], ',');
	tab3 = ft_strsplit(tab[6], '}');
	if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:")))
		w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
		transform, scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
	free_split_tab(tab1, tab2, tab3);
}

void	cyl_crutch_2(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	tab1 = ft_strsplit(tab[2], ',');
	tab2 = ft_strsplit(tab[4], ',');
	tab3 = ft_strsplit(tab[6], '}');
	if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:")))
	{
		w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
		transform, rotation_x(ft_strtodbl(tab1[0])));
		w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
		transform, rotation_y(ft_strtodbl(tab2[0])));
		w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
		transform, rotation_z(ft_strtodbl(tab3[0])));
	}
	else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:")))
		w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
		scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
	else
		cyl_crutch_3(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	cyl_crutch_1(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	tab1 = ft_strsplit(tab[2], ',');
	tab2 = ft_strsplit(tab[4], ',');
	tab3 = ft_strsplit(tab[6], '}');
	if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:")))
	{
		w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
		rotation_x(ft_strtodbl(tab1[0])));
		w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
		rotation_y(ft_strtodbl(tab2[0])));
		w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
		rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		cyl_crutch_2(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	complex_params_cyl(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	if (len_tab(tab) == 7)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], '}');
		if (flag == 1 && !(ft_strcmp(tab[0], "obj_translation:")))
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].
			transform, translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]),
			ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:")))
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
			transform, translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]),
			ft_atoi(tab3[0])));
		else if (flag == 2)
			w->cyl[p->cyl_i].m.color = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else
			cyl_crutch_1(p, w, tab, flag);
		free_split_tab(tab1, tab2, tab3);
	}
}
