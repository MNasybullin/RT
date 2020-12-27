/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: out-nasybullin-mr <out-nasybullin-mr@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:36:46 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/23 19:32:08 by out-nasybul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	make_obj_cyl_4(t_data *p, t_world *w, char **tab)
{
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

void	make_obj_cyl_3(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_sp(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_cyl(tab, p, w);
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
	make_obj_cyl_4(p, w, tab);
}

void	init_cyl(t_data *p, t_world *w)
{
	w->cyl[p->cyl_i] = set_cylinder();
	w->cyl[p->cyl_i].pattern = 0;
	w->cyl[p->cyl_i].is_tex = 0;
	w->cyl[p->cyl_i].pattern_type = 0;
	w->cyl[p->cyl_i].m.tex = 0;
	w->cyl[p->cyl_i].width = 0;
	w->cyl[p->cyl_i].height = 0;
	w->cyl[p->cyl_i].check.height = 0;
	w->cyl[p->cyl_i].check.width = 0;
}

char	**make_cyl(t_data *p, t_world *w, char **tab)
{
	init_cyl(p, w);
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
	//printf("color: %f %f %f\n, amb: %f\nshine %f\ndiffuse %f\n", w->cyl[0].m.color.r, w->cyl[0].m.color.g, w->cyl[0].m.color.b, w->cyl[0].m.ambient, w->cyl[0].m.shininess, w->cyl[0].m.diffuse);
	if ((!(ft_strequ(tab[0], "lights:")) &&
	!(ft_strequ(tab[1], "lights:"))) && (!(ft_strequ(tab[0], "cameras:"))
	&& !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
