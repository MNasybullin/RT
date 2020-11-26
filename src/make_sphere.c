/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:36:11 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 18:45:47 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	complex_params_sphere(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	//ft_putendl("complex params sphere");
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	if (len_tab(tab) == 7)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], '}');
		if (flag == 1 && !(ft_strcmp(tab[0], "obj_translation:"))) // translation
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
			translation(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform,
			translation(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 2) // color
			w->s[p->sp_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
		//ft_putendl("end complex params sphere");
	}
}

void	pattern_color_sp(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	//ft_putendl("pattern color sp");
	if (len_tab(tab) == 7)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], '}');
		if (flag == 1) // color_a
			w->s[p->sp_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->s[p->sp_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	make_obj_sphere(t_data *p, t_world *w, char **tab)
{
	//ft_putendl("make obj sphere");

	if (!(ft_strcmp(tab[0], "specular:")))
		w->s[p->sp_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->s[p->sp_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->s[p->sp_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->s[p->sp_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->s[p->sp_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "pattern:")))
		w->s[p->sp_i].m.pattern = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->s[p->sp_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->s[p->sp_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->s[p->sp_i].m.shadow = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_sphere(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_sphere(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_sphere(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_sphere(p, w, tab, 4);
	//ft_putendl("after all complex params");
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		ft_putendl("strcmp pattern");
		if (!(ft_strcmp(tab[1], "checker")))
			w->s[p->sp_i].pattern = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->s[p->sp_i].pattern = 2;
	}
	if (!(ft_strcmp(tab[0], "color_a")))
		pattern_color_sp(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_a")))
		pattern_color_sp(p, w, tab, 2);
	if (w->s[p->sp_i].pattern)
	{
		//ft_putendl("if pattern");
		if (w->s[p->sp_i].pattern == 1) // checker
			checker_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b, &w->s[p->sp_i].m);
		else if (w->pl[p->pl_i].pattern == 2) // stripe
			stripe_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b, &w->s[p->sp_i].m);
	}
	//ft_putendl("end make obj sphere");
}

char	**make_sphere(t_data *p, t_world *w, char **tab)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	int i = 0;
	int n = 0; // посмотреть сколько раз зайдет в цикл while

	ft_putendl("make sphere");
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	w->s[p->sp_i] = set_sphere();
	tab = NULL;
	w->s[p->sp_i].pattern = 0;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
		{
			make_obj_sphere(p, w, tab);
			n++;
		}
		else
			break ;
	}
	p->sp_i++;
	//printf("\nsphere1: %f\n\n", w->s[0].m.shininess);
	//printf("\nn = %d\n\n", n);
	//if (!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:")))
	//if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:")))/* &&
	//(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:")))*/)
	printf("\nLINE BEFORE GNL IN MAKE SPHERE: %s\n\n", tab[0]);
	if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}