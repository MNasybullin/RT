/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:44:43 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 18:46:31 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	complex_params_cube(t_data *p, t_world *w, char **tab, int flag)
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
		if (flag == 1 && !(ft_strcmp(tab[0], "obj_translation:"))) // translation
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2) // color
			w->cub[p->cube_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->cub[p->cube_i].transform = matrix_mult(w->cub[p->cube_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->cub[p->cube_i].m.p.transform = matrix_mult(w->cub[p->cube_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
	}
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
		if (flag == 1) // color_a
			w->cub[p->cube_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->cub[p->cube_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	make_obj_cube(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "specular:")))
		w->cub[p->cube_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->cub[p->cube_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->cub[p->cube_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->cub[p->cube_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->cub[p->cube_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "pattern:")))
		w->cub[p->cube_i].m.pattern = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->cub[p->cube_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->cub[p->cube_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->cub[p->cube_i].m.shadow = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cube(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cube(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_cube(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_cube(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->cub[p->cube_i].pattern = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->cub[p->cube_i].pattern = 2;
	}
	if (!(ft_strcmp(tab[0], "color_a")))
		pattern_color_cube(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_a")))
		pattern_color_cube(p, w, tab, 2);
	if (w->cub[p->cube_i].pattern)
	{
		if (w->cub[p->cube_i].pattern == 1) // checker
			checker_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b, &w->cub[p->cube_i].m);
		else if (w->cub[p->cube_i].pattern == 2) // stripe
			stripe_pattern_shape(w->cub[p->cube_i].m.p.a, w->cub[p->cube_i].m.p.b, &w->cub[p->cube_i].m);
	}
}

char	**make_cube(t_data *p, t_world *w, char **tab)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;
	int i = 0;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	tab4 = NULL;
	w->cub[p->cube_i] = set_cube();
	w->cub[p->cube_i].pattern = 0;
	//free_tab(tab);
	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		/*if (!(ft_strequ(tab[0], "-")) && !(ft_strequ(tab[0], "object:")) &&
		!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "light:")) &&
		!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:")))*/
		if ((check_make_obj(tab)))
			make_obj_cube(p, w, tab);
		else
			break ;
	}
	p->cube_i++;
	//if (!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:")))
	if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}