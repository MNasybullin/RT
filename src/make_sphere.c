/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:36:11 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/22 22:57:42 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
