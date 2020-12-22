/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:19:38 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/22 19:43:18 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	make_obj_cone_3(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
	{
		if (len_tab(tab) == 2)
		{
			if (!(ft_strcmp(tab[1], "1")))
				w->cone[p->cone_i].m.tex = 1;
		}
	}
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
		w->cone[p->cone_i].texture = ft_strdup(remove_quotes(tab[1]));
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

void	make_obj_cone_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "min:")))
		w->cone[p->cone_i].min = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "max:")))
		w->cone[p->cone_i].max = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "closed:")))
		w->cone[p->cone_i].closed = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cone(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cone(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0],
	"m_rotation:")))
		complex_params_cone(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0],
	"m_scaling:")))
		complex_params_cone(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->cone[p->cone_i].m.pattern = 1;
	}
	if (!(ft_strcmp(tab[0], "pattern_type:")))
		pattern_type_cone(p, w, tab);
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
	make_obj_cone_2(p, w, tab);
	make_obj_cone_3(p, w, tab);
}

void	init_cone(t_data *p, t_world *w)
{
	w->cone[p->cone_i] = set_cone();
	w->cone[p->cone_i].pattern = 0;
	w->cone[p->cone_i].is_tex = 0;
	w->cone[p->cone_i].pattern_type = 0;
	w->cone[p->cone_i].m.tex = 0;
	w->cone[p->cone_i].width = 0;
	w->cone[p->cone_i].height = 0;
}

char	**make_cone(t_data *p, t_world *w, char **tab)
{
	init_cone(p, w);
	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_cone(p, w, tab);
		else
			break ;
	}
	if (w->cone[p->cone_i].m.pattern == 1)
		cone_patterns(p, w);
	p->cone_i++;
	if (len_tab(tab) >= 2 && (!(ft_strequ(tab[0], "lights:"))
	&& !(ft_strequ(tab[1], "light:"))) && (!(ft_strequ(tab[0], "cameras:"))
	&& !(ft_strequ(tab[1], "camera:"))))
		p->tab = ft_strsplit(p->line, ' ');
	return (p->tab);
}
