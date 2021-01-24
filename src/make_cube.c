/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:44:43 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/24 18:36:55 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	cube_crutch_3(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	tab1 = ft_strsplit(tab[2], ',');
	tab2 = ft_strsplit(tab[4], ',');
	tab3 = ft_strsplit(tab[6], '}');
	if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:")))
		w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
		scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
	else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:")))
		w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.
		transform, scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
	free_split_tab(tab1, tab2, tab3);
}

void	cube_crutch_2(t_data *p, t_world *w, char **tab, int flag)
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
		w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.
		transform, rotation_x(ft_strtodbl(tab1[0])));
		w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.
		transform, rotation_y(ft_strtodbl(tab2[0])));
		w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.
		transform, rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		cube_crutch_3(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	cube_crutch_1(t_data *p, t_world *w, char **tab, int flag)
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
		w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
		rotation_x(ft_strtodbl(tab1[0])));
		w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
		rotation_y(ft_strtodbl(tab2[0])));
		w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
		rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		cube_crutch_2(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	complex_params_cube(t_data *p, t_world *w, char **tab, int flag)
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
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].
			transform, translation(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
			ft_strtodbl(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:")))
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].
			m.p.transform, translation(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
			ft_strtodbl(tab3[0])));
		else if (flag == 2)
			w->cub[p->cube_i].m.color = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else
			cube_crutch_1(p, w, tab, flag);
		free_split_tab(tab1, tab2, tab3);
	}
}

char	**make_cube(t_data *p, t_world *w, char **tab)
{
	init_cube(p, w, tab);
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_cube(p, w, tab);
		else
			break ;
	}
	if (w->cub[p->cube_i].m.pattern == 1)
	{
		w->cub[p->cube_i].m.pattern_at = &pattern_at_cube_texture;
		if (w->cub[p->cube_i].m.tex == 1)
			make_tex_cube(p, w);
	}
	if (w->cub[p->cube_i].pattern_type != 0)
		cube_patterns(p, w);
	p->cube_i++;
	if ((final_if_cube(tab)))
	{
		//get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
