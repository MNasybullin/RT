/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:49:57 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 14:05:04 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	make_obj_tri_4(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_tri(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_tri(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "width:")))
		w->trian[p->tri_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->trian[p->tri_i].height = ft_atoi(tab[1]);
}

void	make_obj_tri_3(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->trian[p->tri_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->trian[p->tri_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "ring")))
			w->trian[p->tri_i].pattern_type = 3;
		if (!(ft_strcmp(tab[1], "gradient")))
			w->trian[p->tri_i].pattern_type = 4;
	}
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->trian[p->tri_i].m.pattern = 1;
	}
	/*if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_tri(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_tri(p, w, tab, 2);*/
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_tri(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
		w->trian[p->tri_i].texture = ft_strdup(remove_quotes(tab[1]));
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->trian[p->tri_i].is_tex++;
	}
}

void	make_obj_tri_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_tri(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_tri(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) ||
	!(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_tri(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) ||
	!(ft_strcmp(tab[0], "m_scaling:")))
		complex_params_tri(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "p1:")))
	{
		p->tri_vect++;
		triangle_sides(p, w, tab, 5);
	}
	if (!(ft_strcmp(tab[0], "p2:")))
	{
		p->tri_vect++;
		triangle_sides(p, w, tab, 6);
	}
	if (!(ft_strcmp(tab[0], "p3:")))
	{
		p->tri_vect++;
		triangle_sides(p, w, tab, 7);
	}
}

void	make_obj_tri(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "specular:")))
		w->trian[p->tri_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->trian[p->tri_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->trian[p->tri_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->trian[p->tri_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->trian[p->tri_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "pattern:")))
		w->trian[p->tri_i].m.pattern = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->trian[p->tri_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->trian[p->tri_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->trian[p->tri_i].m.shadow = ft_atoi(tab[1]);
	make_obj_tri_2(p, w, tab);
	make_obj_tri_3(p, w, tab);
	make_obj_tri_4(p, w, tab);
}

char	**make_tri(t_data *p, t_world *w, char **tab)
{
	tab = NULL;
	init_tri(p, w);
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_tri(p, w, tab);
		else
			break ;
	}
	if (p->tri_vect == 3)
		set_trian(w->trian[p->tri_i].p1, w->trian[p->tri_i].p2,
		w->trian[p->tri_i].p3, &w->trian[p->tri_i]);
	if (w->trian[p->tri_i].m.pattern == 1)
		tri_patterns(p, w);
	p->tri_vect = 0;
	p->tri_i++;
	if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		p->tab = ft_strsplit(p->line, ' ');
	}
	return (p->tab);
}
