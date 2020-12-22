/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:36:11 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/22 22:25:47 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	sp_crutch_2(t_data *p, t_world *w, char **tab, int flag)
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
		w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform,
		rotation_x(ft_strtodbl(tab1[0])));
		w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform,
		rotation_y(ft_strtodbl(tab2[0])));
		w->s[p->sp_i].m.p.transform = matrix_mult(w->s[p->sp_i].m.p.transform,
		rotation_z(ft_strtodbl(tab3[0])));
	}
	else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:")))
		w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
		scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
		ft_strtodbl(tab3[0])));
	else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:")))
		w->s[p->sp_i].m.p.transform = matrix_mult(w->
		s[p->sp_i].m.p.transform, scaling(ft_strtodbl(tab1[0]),
		ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
	free_split_tab(tab1, tab2, tab3);
}

void	sp_crutch_1(t_data *p, t_world *w, char **tab, int flag)
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
		w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
		rotation_x(ft_strtodbl(tab1[0])));
		w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
		rotation_y(ft_strtodbl(tab2[0])));
		w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
		rotation_z(ft_strtodbl(tab3[0])));
	}
	else
		sp_crutch_2(p, w, tab, flag);
	free_split_tab(tab1, tab2, tab3);
}

void	complex_params_sphere(t_data *p, t_world *w, char **tab, int flag)
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
			w->s[p->sp_i].transform = matrix_mult(w->s[p->sp_i].transform,
			translation(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]),
			ft_strtodbl(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:")))
			w->s[p->sp_i].m.p.transform = matrix_mult(w->
			s[p->sp_i].m.p.transform, translation(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 2)
			w->s[p->sp_i].m.color = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else
			sp_crutch_1(p, w, tab, flag);
		free_split_tab(tab1, tab2, tab3);
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
	if (len_tab(tab) == 7)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], '}');
		if (flag == 1)
			w->s[p->sp_i].m.p.a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2)
			w->s[p->sp_i].m.p.b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->s[p->sp_i].color_a = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->s[p->sp_i].color_b = color(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	texture_sp(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->s[p->sp_i].m.tex = 1;
	}
}

void	pattern_type_sphere(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[1], "checker")))
			w->s[p->sp_i].pattern_type = 1;
	if (!(ft_strcmp(tab[1], "stripe")))
		w->s[p->sp_i].pattern_type = 2;
	if (!(ft_strcmp(tab[1], "gradient")))
		w->s[p->sp_i].pattern_type = 3;
	if (!(ft_strcmp(tab[1], "ring")))
		w->s[p->sp_i].pattern_type = 4;
	if (!(ft_strcmp(tab[1], "1")))
		w->s[p->sp_i].m.pattern = 1;
}

void	make_obj_sphere_3(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->s[p->sp_i].m.pattern = 1;
	}
	if (!(ft_strcmp(tab[0], "pattern_type:")))
		pattern_type_sphere(p, w, tab);
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_sp(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
		w->s[p->sp_i].texture = ft_strdup(remove_quotes(tab[1]));
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->s[p->sp_i].is_tex++;
	}
}

void	make_obj_sphere_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_sphere(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_sphere(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) ||
	!(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_sphere(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) ||
	!(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_sphere(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_sp(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_sp(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_sp(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_sp(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "width:")))
		w->s[p->sp_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->s[p->sp_i].height = ft_atoi(tab[1]);
}

void	make_obj_sphere(t_data *p, t_world *w, char **tab)
{
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
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->s[p->sp_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->s[p->sp_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->s[p->sp_i].m.shadow = ft_atoi(tab[1]);
	make_obj_sphere_2(p, w, tab);
	make_obj_sphere_3(p, w, tab);
}

/*void	make_tex_sp(t_data *p, t_world *w)
{
	t_uv_check check;
	//if (w->s[p->sp_i].m.pattern == 1 && (w->s[p->sp_i].pattern_type == 1
	//|| w->s[p->sp_i].pattern_type == 2))
	//{
		//ft_putendl("\n\nin texture if\n\n");
		w->s[p->sp_i].m.pattern_at = &pattern_at;
		if (w->s[p->sp_i].pattern_type == 1)
		{
			check.color_a = w->s[p->sp_i].color_a;
			check.color_b = w->s[p->sp_i].color_b;
			check.width = w->s[p->sp_i].width;
			check.height = w->s[p->sp_i].height;
			uv_checkers(check, &w->s[p->sp_i].m.p);
		}
		else if (w->s[p->sp_i].pattern_type == 2)
			stripe_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
			&w->s[p->sp_i].m);
		if (w->s[p->sp_i].m.tex == 1)
		{
			w->s[p->sp_i].m.texturemap = texture_map(w->s[p->sp_i].m.p,
			&spherical_map);
			w->s[p->sp_i].m.texture = SDL_LoadBMP(w->s[p->sp_i].texture);
		}
}*/

void	init_sphere(t_data *p, t_world *w)
{
	w->s[p->sp_i] = set_sphere();
	w->s[p->sp_i].pattern = 0;
	w->s[p->sp_i].is_tex = 0;
	w->s[p->sp_i].pattern_type = 0;
	w->s[p->sp_i].m.tex = 0;
	w->s[p->sp_i].width = 0;
	w->s[p->sp_i].height = 0;
	w->s[p->sp_i].check.width = 0;
	w->s[p->sp_i].check.height = 0;
}

void	sphere_patterns_1(t_data *p, t_world *w)
{
	w->s[p->sp_i].check.color_a = w->s[p->sp_i].color_a;
	w->s[p->sp_i].check.color_b = w->s[p->sp_i].color_b;
	w->s[p->sp_i].check.width = w->s[p->sp_i].width;
	w->s[p->sp_i].check.height = w->s[p->sp_i].height;
	uv_checkers(w->s[p->sp_i].check, &w->s[p->sp_i].m.p);
}

void	sphere_patterns(t_data *p, t_world *w)
{
	w->s[p->sp_i].m.pattern_at = &pattern_at;
	if (w->s[p->sp_i].pattern_type == 1)
		sphere_patterns_1(p, w);
	else if (w->s[p->sp_i].pattern_type == 2)
		stripe_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	else if (w->s[p->sp_i].pattern_type == 3)
		gradient_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	else if (w->s[p->sp_i].pattern_type == 4)
		ring_pattern_shape(w->s[p->sp_i].m.p.a, w->s[p->sp_i].m.p.b,
		&w->s[p->sp_i].m);
	if (w->s[p->sp_i].m.tex == 1)
	{
		w->s[p->sp_i].m.texture = SDL_LoadBMP(w->s[p->sp_i].texture);
		w->s[p->sp_i].m.texturemap = texture_map(w->s[p->sp_i].m.p,
		&spherical_map);
	}
	if ((w->s[p->sp_i].pattern_type < 1 || w->s[p->sp_i].pattern_type > 4)
	&& w->s[p->sp_i].m.tex != 1)
		w->s[p->sp_i].m.pattern = 0;
}

char	**make_sphere(t_data *p, t_world *w, char **tab)
{
	tab = NULL;
	init_sphere(p, w);
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_sphere(p, w, tab);
		else
			break ;
	}
	if (w->s[p->sp_i].m.pattern == 1)
		sphere_patterns(p, w);
	p->sp_i++;
	if ((!(ft_strequ(tab[0], "lights:")) && (len_tab(tab) == 2 &&
	!(ft_strequ(tab[1], "lights:")))) && (len_tab(tab) == 2 &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:")))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
