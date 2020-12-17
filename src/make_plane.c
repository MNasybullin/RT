/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:10:33 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/17 19:55:40 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	complex_params_plane(t_data *p, t_world *w, char **tab, int flag)
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
			w->pl[p->pl_i].transform = matrix_mult(w->pl[p->pl_i].transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->pl[p->pl_i].m.p.transform = matrix_mult(w->pl[p->pl_i].m.p.transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2) // color
			w->pl[p->pl_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->pl[p->pl_i].transform = matrix_mult(w->pl[p->pl_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->pl[p->pl_i].transform = matrix_mult(w->pl[p->pl_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->pl[p->pl_i].transform = matrix_mult(w->pl[p->pl_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->pl[p->pl_i].m.p.transform = matrix_mult(w->pl[p->pl_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->pl[p->pl_i].m.p.transform = matrix_mult(w->pl[p->pl_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->pl[p->pl_i].m.p.transform = matrix_mult(w->pl[p->pl_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->pl[p->pl_i].transform = matrix_mult(w->pl[p->pl_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->pl[p->pl_i].m.p.transform = matrix_mult(w->pl[p->pl_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
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
		if (flag == 1) // color_a
			w->pl[p->pl_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->pl[p->pl_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->pl[p->pl_i].color_a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->pl[p->pl_i].color_b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
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

void	make_obj_plane(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "specular:")))
		w->pl[p->pl_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->pl[p->pl_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->pl[p->pl_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->pl[p->pl_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->pl[p->pl_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->pl[p->pl_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->pl[p->pl_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->pl[p->pl_i].m.shadow = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_plane(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_plane(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_plane(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_plane(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")) && !(ft_strcmp(tab[1], "1")))
		w->pl[p->pl_i].m.pattern = 1;
	//ft_putendl("after all complex params");
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->pl[p->pl_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->pl[p->pl_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "gradient")))
			w->pl[p->pl_i].pattern_type = 3;
		if (!(ft_strcmp(tab[1], "ring")))
			w->pl[p->pl_i].pattern_type = 4;
		w->pl[p->pl_i].m.pattern = 1;
	}
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_sp(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
	{
		//texture_sp(tab, p, w);
		w->pl[p->pl_i].texture = ft_strdup(remove_quotes(tab[1]));
		w->pl[p->pl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->pl[p->pl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_pl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_pl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_pl(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_pl(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "width:")))
		w->pl[p->pl_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->pl[p->pl_i].height = ft_atoi(tab[1]);
}

void	init_plane(t_data *p, t_world *w)
{
	w->pl[p->pl_i] = set_plane();
	w->pl[p->pl_i].pattern = 0;
	w->pl[p->pl_i].is_tex = 0;
	w->pl[p->pl_i].pattern_type = 0;
	w->pl[p->pl_i].m.tex = 0;
	w->pl[p->pl_i].width = 0;
	w->pl[p->pl_i].height = 0;
	w->pl[p->pl_i].color_a.r = 0;
	w->pl[p->pl_i].color_a.g = 0;
	w->pl[p->pl_i].color_a.b = 0;
}

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

char	**make_plane(t_data *p, t_world *w, char **tab)
{
	init_plane(p, w);
	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_plane(p, w, tab);
		else
			break ;
	}
	//printf("pattern color a: %f %f %f\nwidth: %d\nheight:%d\n", w->pl[0].color_a.r, w->pl[0].color_a.g, w->pl[0].color_a.b, w->pl[0].width, w->pl[0].height);
	if (w->pl[p->pl_i].m.pattern == 1)
		plane_patterns(p, w);
	p->pl_i++;
	if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
