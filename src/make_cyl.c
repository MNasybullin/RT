/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:36:46 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/08 17:44:14 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	complex_params_cyl(t_data *p, t_world *w, char **tab, int flag)
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
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2) // color
			w->cyl[p->cyl_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->cyl[p->cyl_i].transform = matrix_mult(w->cyl[p->cyl_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->cyl[p->cyl_i].m.p.transform = matrix_mult(w->cyl[p->cyl_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
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
		if (flag == 1) // color_a
			w->cyl[p->cyl_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->cyl[p->cyl_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->cyl[p->cyl_i].color_a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->cyl[p->cyl_i].color_b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
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
    if (!(ft_strcmp(tab[0], "min:")))
		w->cyl[p->cyl_i].min = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "max:")))
		w->cyl[p->cyl_i].max = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "closed:")))
		w->cyl[p->cyl_i].closed = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cyl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cyl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_cyl(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_cyl(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		//printf("\n1 if\n");
		if (!(ft_strcmp(tab[1], "1")))
		{
			//printf("\n2 if\n");
			w->cyl[p->cyl_i].m.pattern = 1;
			//w->cub[p->cube_i].m.pattern_at = &pattern_at_cube_texture;
			//w->cyl[p->cyl_i].m.p.transform = identity_matrix();
		}
	}
	//ft_putendl("after all complex params");
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->cyl[p->cyl_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->cyl[p->cyl_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "1")))
		{
			w->cyl[p->cyl_i].m.pattern = 1;
			w->cyl[p->cyl_i].is_tex++;
		}
	}
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_cyl(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
	{
		//texture_sp(tab, p, w);
		w->cyl[p->cyl_i].texture = ft_strdup(remove_quotes(tab[1]));
		w->cyl[p->cyl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cyl[p->cyl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_cyl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_cyl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_sp(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_sp(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "width:")))
		w->cyl[p->cyl_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->cyl[p->cyl_i].height = ft_atoi(tab[1]);
}

char	**make_cyl(t_data *p, t_world *w, char **tab)
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
	w->cyl[p->cyl_i] = set_cylinder();
	//free_tab(tab);
	tab = NULL;
	w->cyl[p->cyl_i].pattern = 0;
	w->cyl[p->cyl_i].is_tex = 0;
	w->cyl[p->cyl_i].pattern_type = 0;
	w->cyl[p->cyl_i].m.tex = 0;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_cyl(p, w, tab);
		else
			break ;
	}
	if (w->cyl[p->cyl_i].m.pattern == 1 && (w->cyl[p->cyl_i].pattern_type == 1
	|| w->cyl[p->cyl_i].pattern_type == 2))
	{
		//ft_putendl("\n\nin texture if\n\n");
		w->cyl[p->cyl_i].m.pattern_at = &pattern_at;
		//w->cyl[p->cyl_i].m.p.transform = identity_matrix();
		if (w->cyl[p->cyl_i].pattern_type == 1)
		{
			check.color_a = w->cyl[p->cyl_i].color_a;
			check.color_b = w->cyl[p->cyl_i].color_b;
			check.width = w->cyl[p->cyl_i].width;
			check.height = w->cyl[p->cyl_i].height;
			uv_checkers(check, &w->cyl[p->cyl_i].m.p);
		}
		else if (w->cyl[p->cyl_i].pattern_type == 2)
			stripe_pattern_shape(w->cyl[p->cyl_i].m.p.a, w->cyl[p->cyl_i].m.p.b,
			&w->cyl[p->cyl_i].m);
		if (w->cyl[p->cyl_i].m.tex == 1)
		{
			w->cyl[p->cyl_i].m.texturemap = texture_map(w->cyl[p->cyl_i].m.p,
			&cylindrical_map);
			w->cyl[p->cyl_i].m.texture = SDL_LoadBMP(w->cyl[p->cyl_i].texture);
		}
	}
	p->cyl_i++;
	if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
