/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:19:38 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/08 19:59:59 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	complex_params_cone(t_data *p, t_world *w, char **tab, int flag)
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
			w->cone[p->cone_i].transform = matrix_mult(w->cone[p->cone_i].transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->cone[p->cone_i].m.p.transform = matrix_mult(w->cone[p->cone_i].m.p.transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2) // color
			w->cone[p->cone_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->cone[p->cone_i].transform = matrix_mult(w->cone[p->cone_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cone[p->cone_i].transform = matrix_mult(w->cone[p->cone_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cone[p->cone_i].transform = matrix_mult(w->cone[p->cone_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->cone[p->cone_i].m.p.transform = matrix_mult(w->cone[p->cone_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cone[p->cone_i].m.p.transform = matrix_mult(w->cone[p->cone_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cone[p->cone_i].m.p.transform = matrix_mult(w->cone[p->cone_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->cone[p->cone_i].transform = matrix_mult(w->cone[p->cone_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->cone[p->cone_i].m.p.transform = matrix_mult(w->cone[p->cone_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
	}
}

void	pattern_color_cone(t_data *p, t_world *w, char **tab, int flag)
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
			w->cone[p->cone_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->cone[p->cone_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->cone[p->cone_i].color_a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->cone[p->cone_i].color_b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	texture_cone(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cone[p->cone_i].m.tex = 1;
	}
}

void	make_obj_cone(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "specular:")))
		w->cone[p->cone_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->cone[p->cone_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->cone[p->cone_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->cone[p->cone_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->cone[p->cone_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "pattern:")))
		w->cone[p->cone_i].m.pattern = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->cone[p->cone_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->cone[p->cone_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->cone[p->cone_i].m.shadow = ft_atoi(tab[1]);
    if (!(ft_strcmp(tab[0], "min:")))
		w->cone[p->cone_i].min = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "max:")))
		w->cone[p->cone_i].max = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "closed:")))
		w->cone[p->cone_i].closed = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cone(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cone(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_cone(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_cone(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cone[p->cone_i].m.pattern = 1;
	}
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->cone[p->cone_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->cone[p->cone_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "gradient")))
			w->cone[p->cone_i].pattern_type = 3;
		if (!(ft_strcmp(tab[1], "ring")))
			w->cone[p->cone_i].pattern_type = 4;
		if (!(ft_strcmp(tab[1], "1")))
		{
			w->cone[p->cone_i].m.pattern = 1;
			w->cone[p->cone_i].is_tex++;
		}
	}
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_cone(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
	{
		//texture_sp(tab, p, w);
		w->cone[p->cone_i].texture = ft_strdup(remove_quotes(tab[1]));
		w->cone[p->cone_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cone[p->cone_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_cone(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_cone(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_cone(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_cone(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "width:")))
		w->cone[p->cone_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->cone[p->cone_i].height = ft_atoi(tab[1]);
}

char	**make_cone(t_data *p, t_world *w, char **tab)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;
	t_uv_check check;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	tab4 = NULL;
	w->cone[p->cone_i] = set_cone();
	//free_tab(tab);
	tab = NULL;
	w->cone[p->cone_i].pattern = 0;
	w->cone[p->cone_i].is_tex = 0;
	w->cone[p->cone_i].pattern_type = 0;
	w->cone[p->cone_i].m.tex = 0;
	w->cone[p->cone_i].width = 0;
	w->cone[p->cone_i].height = 0;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
		{
			ft_putendl("\n\nin if\n\n");
			make_obj_cone(p, w, tab);
		}
		else
			break ;
	}
	if (w->cone[p->cone_i].m.pattern == 1)
	{
		//ft_putendl("\n\nin texture if\n\n");
		w->cone[p->cone_i].m.pattern_at = &pattern_at;
		//w->cone[p->cone_i].m.p.transform = identity_matrix();
		if (w->cone[p->cone_i].pattern_type == 1)
		{
			check.color_a = w->cone[p->cone_i].color_a;
			check.color_b = w->cone[p->cone_i].color_b;
			check.width = w->cone[p->cone_i].width;
			check.height = w->cone[p->cone_i].height;
			uv_checkers(check, &w->cone[p->cone_i].m.p);
		}
		else if (w->cone[p->cone_i].pattern_type == 2)
			stripe_pattern_shape(w->cone[p->cone_i].m.p.a, w->cone[p->cone_i].m.p.b,
			&w->cone[p->cone_i].m);
		else if (w->cone[p->cone_i].pattern_type == 3)
			gradient_pattern_shape(w->cone[p->cone_i].m.p.a, w->cone[p->cone_i].m.p.b,
			&w->cone[p->cone_i].m);
		else if (w->cone[p->cone_i].pattern_type == 4)
			ring_pattern_shape(w->cone[p->cone_i].m.p.a, w->cone[p->cone_i].m.p.b,
			&w->cone[p->cone_i].m);
		if (w->cone[p->cone_i].m.tex == 1)
		{
			w->cone[p->cone_i].m.texture = SDL_LoadBMP(w->cone[p->cone_i].texture);
			w->cone[p->cone_i].m.texturemap = texture_map(w->cone[p->cone_i].m.p,
			&cylindrical_map);
			
		}
	}
	p->cone_i++;
	if (len_tab(tab) >= 2 && (!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "light:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		//get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	//printf("\n\ntab[0] in make cone %s\n", p->tab[0]);
	return (p->tab);
}
