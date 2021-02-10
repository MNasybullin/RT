/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:27:09 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 14:00:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	tri_crutch_3(t_data *p, t_world *w, char **tab, int flag)
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
		tri_m_rotation(p, w, tab1, tab2);
		w->trian[p->tri_i].m.p.transform = matrix_mult(w->
		trian[p->tri_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
	}
	else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:")))
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, scaling(ft_strtodbl(tab1[0]),
		ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
	else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:")))
		w->trian[p->tri_i].m.p.transform = matrix_mult(w->
		trian[p->tri_i].m.p.transform, scaling(ft_strtodbl(tab1[0]),
		ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
	free_split_tab(tab1, tab2, tab3);
}

void	tri_crutch_2(t_data *p, t_world *w, char **tab, int flag)
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
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_x(ft_strtodbl(tab1[0])));
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_y(ft_strtodbl(tab2[0])));
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		tri_crutch_3(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	tri_crutch_1(t_data *p, t_world *w, char **tab, int flag)
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
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_x(ft_strtodbl(tab1[0])));
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_y(ft_strtodbl(tab2[0])));
		w->trian[p->tri_i].transform = matrix_mult(w->
		trian[p->tri_i].transform, rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		tri_crutch_2(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	complex_params_tri(t_data *p, t_world *w, char **tab, int flag)
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
			w->trian[p->tri_i].transform = matrix_mult(w->
			trian[p->tri_i].transform, translation(ft_atoi(tab1[0]),
			ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:")))
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->
			trian[p->tri_i].m.p.transform, translation(ft_atoi(tab1[0]),
			ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2)
			w->trian[p->tri_i].m.color = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else
			tri_crutch_1(p, w, tab, flag);
		free_split_tab(tab1, tab2, tab3);
	}
}

void	pattern_color_tri(t_data *p, t_world *w, char **tab, int flag)
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
			w->trian[p->tri_i].m.p.a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2)
			w->trian[p->tri_i].m.p.b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		/*else if (flag == 3)
			w->trian[p->tri_i].color_a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->trian[p->tri_i].color_b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));*/
	}
}
