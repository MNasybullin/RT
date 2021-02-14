/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:10:33 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 15:02:59 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	make_obj_plane_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->pl[p->pl_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_pl(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_pl(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_sp(tab, p, w);
	if (!(ft_strcmp(tab[0], "height:")))
		w->pl[p->pl_i].height = ft_atoi(tab[1]);
}

void	make_obj_plane_1(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "obj_rotation:")) ||
	!(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_plane(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) ||
	!(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_plane(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")) && !(ft_strcmp(tab[1], "1")))
		w->pl[p->pl_i].m.pattern = 1;
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
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
		w->pl[p->pl_i].texture = ft_strdup(remove_quotes(tab[1]));
	if (!(ft_strcmp(tab[0], "width:")))
		w->pl[p->pl_i].width = ft_atoi(tab[1]);
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
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_plane(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_plane(p, w, tab, 2);
	make_obj_plane_1(p, w, tab);
	make_obj_plane_2(p, w, tab);
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
