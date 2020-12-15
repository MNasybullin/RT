/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:36:46 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/15 18:16:10 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
	if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:")))
		w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.
		transform, scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
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
		else if (flag == 3)
			w->cyl[p->cyl_i].color_a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->cyl[p->cyl_i].color_b = color(ft_strtodbl(tab1[0]),
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

void	make_obj_cyl_3(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->cyl[p->cyl_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->cyl[p->cyl_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "gradient")))
			w->cyl[p->cyl_i].pattern_type = 3;
		if (!(ft_strcmp(tab[1], "ring")))
			w->cyl[p->cyl_i].pattern_type = 4;
		if (!(ft_strcmp(tab[1], "1")))
		{
			w->cyl[p->cyl_i].m.pattern = 1;
			w->cyl[p->cyl_i].is_tex++;
		}
	}
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
	{
		w->cyl[p->cyl_i].texture = ft_strdup(remove_quotes(tab[1]));
		w->cyl[p->cyl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cyl[p->cyl_i].is_tex++;
	}
}

void	make_obj_cyl_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "min:")))
		w->cyl[p->cyl_i].min = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "max:")))
		w->cyl[p->cyl_i].max = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "closed:")))
		w->cyl[p->cyl_i].closed = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cyl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cyl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) ||
	!(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_cyl(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) ||
	!(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_cyl(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")) && !(ft_strcmp(tab[1], "1")))
			w->cyl[p->cyl_i].m.pattern = 1;
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_cyl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_cyl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_sp(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_sp(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_cyl(tab, p, w);
}

void	make_obj_cyl(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "specular:")))
		w->cyl[p->cyl_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->cyl[p->cyl_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->cyl[p->cyl_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->cyl[p->cyl_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->cyl[p->cyl_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "pattern:")))
		w->cyl[p->cyl_i].m.pattern = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->cyl[p->cyl_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->cyl[p->cyl_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->cyl[p->cyl_i].m.shadow = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "width:")))
		w->cyl[p->cyl_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->cyl[p->cyl_i].height = ft_atoi(tab[1]);
	make_obj_cyl_2(p, w, tab);
	make_obj_cyl_3(p, w, tab);
}

void	init_cyl(t_data *p, t_world *w, char **tab)
{
	w->cyl[p->cyl_i] = set_cylinder();
	tab = NULL;
	w->cyl[p->cyl_i].pattern = 0;
	w->cyl[p->cyl_i].is_tex = 0;
	w->cyl[p->cyl_i].pattern_type = 0;
	w->cyl[p->cyl_i].m.tex = 0;
}

void	cyl_patterns_1(t_data *p, t_world *w, t_uv_check check)
{
	check.color_a = w->cyl[p->cyl_i].color_a;
	check.color_b = w->cyl[p->cyl_i].color_b;
	check.width = w->cyl[p->cyl_i].width;
	check.height = w->cyl[p->cyl_i].height;
	uv_checkers(check, &w->cyl[p->cyl_i].m.p);
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

char	**make_cyl(t_data *p, t_world *w, char **tab)
{
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_cyl(p, w, tab);
		else
			break ;
	}
	if (w->cyl[p->cyl_i].m.pattern == 1)
		cyl_patterns(p, w);
	p->cyl_i++;
	if ((!(ft_strequ(tab[0], "lights:")) &&
	!(ft_strequ(tab[1], "lights:"))) && (!(ft_strequ(tab[0], "cameras:"))
	&& !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
