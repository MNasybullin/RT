/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:49:57 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/08 18:58:56 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	triangle_sides(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	tab4 = NULL;
	if (len_tab(tab) == 9)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], ',');
		tab4 = ft_strsplit(tab[8], '}');
		if (flag == 5) // p1
			w->trian[p->tri_i].p1 = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		else if (flag == 6) // p2
			w->trian[p->tri_i].p2 = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		else if (flag == 7) // p3
			w->trian[p->tri_i].p3 = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		free_tab(tab4);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
		tab4 = NULL;
	}
}

void	complex_params_tri(t_data *p, t_world *w, char **tab, int flag)
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
			w->trian[p->tri_i].transform = matrix_mult(w->trian[p->tri_i].transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 1 && !(ft_strcmp(tab[0], "m_translation:"))) // translation
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->trian[p->tri_i].m.p.transform,
			translation(ft_atoi(tab1[0]), ft_atoi(tab2[0]), ft_atoi(tab3[0])));
		else if (flag == 2) // color
			w->trian[p->tri_i].m.color = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3 && !(ft_strcmp(tab[0], "obj_rotation:"))) // rotation
		{
			w->trian[p->tri_i].transform = matrix_mult(w->trian[p->tri_i].transform, rotation_x(ft_strtodbl(tab1[0])));
			w->trian[p->tri_i].transform = matrix_mult(w->trian[p->tri_i].transform, rotation_y(ft_strtodbl(tab2[0])));
			w->trian[p->tri_i].transform = matrix_mult(w->trian[p->tri_i].transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 3 && !(ft_strcmp(tab[0], "m_rotation:"))) // rotation
		{
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->trian[p->tri_i].m.p.transform, rotation_x(ft_strtodbl(tab1[0])));
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->trian[p->tri_i].m.p.transform, rotation_y(ft_strtodbl(tab2[0])));
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->trian[p->tri_i].m.p.transform, rotation_z(ft_strtodbl(tab3[0])));
		}
		else if (flag == 4 && !(ft_strcmp(tab[0], "obj_scaling:"))) // scaling
			w->trian[p->tri_i].transform = matrix_mult(w->trian[p->tri_i].transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		else if (flag == 4 && !(ft_strcmp(tab[0], "m_scaling:"))) // scaling
			w->trian[p->tri_i].m.p.transform = matrix_mult(w->trian[p->tri_i].m.p.transform,
			scaling(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0])));
		free_tab(tab1);
		free_tab(tab2);
		free_tab(tab3);
		tab1 = NULL;
		tab2 = NULL;
		tab3 = NULL;
	}
}

void	pattern_color_tri(t_data *p, t_world *w, char **tab, int flag)
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
			w->trian[p->tri_i].m.p.a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 2) // color_b
			w->trian[p->tri_i].m.p.b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 3)
			w->trian[p->tri_i].color_a = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
		else if (flag == 4)
			w->trian[p->tri_i].color_b = color(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]));
	}
}

void	texture_tri(char **tab, t_data *p, t_world *w)
{
	if (len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->trian[p->tri_i].m.tex = 1;
	}
}

void	make_obj_tri(t_data *p, t_world *w, char **tab)
{
	//ft_putendl("\n\nmake obj tri\n\n");
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
	if (!(ft_strcmp(tab[0], "obj_translation:")) || !(ft_strcmp(tab[0], "m_translation:")))
		complex_params_tri(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_tri(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0], "m_rotation:")))
		complex_params_tri(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0], "m_scaling:")))
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
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->trian[p->tri_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->trian[p->tri_i].pattern_type = 2;
	}
	if (!(ft_strcmp(tab[0], "pattern:")))
	{
		//printf("\n1 if\n");
		if (!(ft_strcmp(tab[1], "1")))
		{
			//printf("\n2 if\n");
			w->trian[p->tri_i].m.pattern = 1;
			//w->cub[p->cube_i].m.pattern_at = &pattern_at_cube_texture;
		}
	}
	if (!(ft_strcmp(tab[0], "color_a:")))
		pattern_color_tri(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color_b:")))
		pattern_color_tri(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "tex:")) && len_tab(tab) == 2)
		texture_tri(tab, p, w);
	if (!(ft_strcmp(tab[0], "texture:")) && len_tab(tab) == 2)
	{
		//texture_sp(tab, p, w);
		//ft_putendl("\n\nin if texture\n");
		w->trian[p->tri_i].texture = ft_strdup(remove_quotes(tab[1]));
		w->trian[p->tri_i].is_tex++;
		//ft_putendl("\n\nend of if texture\n");
		printf("\n\nTRI TEXTURE IN MAKE TRI: %s\n\n", w->trian[p->tri_i].texture);
	}
	if (!(ft_strcmp(tab[0], "texturemap:")) && len_tab(tab) == 2)
	{
		if (!(ft_strcmp(tab[1], "1")))
			w->trian[p->tri_i].is_tex++;
	}
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_tri(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_tri(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "width:")))
		w->trian[p->tri_i].width = ft_atoi(tab[1]);
	if (!(ft_strcmp(tab[0], "height:")))
		w->trian[p->tri_i].height = ft_atoi(tab[1]);
	//ft_putendl("\n\nend of make obj tri\n\n");
}

char	**make_tri(t_data *p, t_world *w, char **tab)
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
	//w->trian[p->tri_i] = set_trian();
	//free_tab(tab);
	tab = NULL;
	w->trian[p->tri_i].pattern = 0;
	p->tri_vect = 0;
	w->trian[p->tri_i].pattern = 0;
	w->trian[p->tri_i].is_tex = 0;
	w->trian[p->tri_i].pattern_type = 0;
	w->trian[p->tri_i].m.tex = 0;
	w->trian[p->tri_i].width = 0;
	w->trian[p->tri_i].height = 0;
	ft_putendl("\n\nin make tri\n\n");
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(tab)))
			make_obj_tri(p, w, tab);
		else
			break ;
	}
	ft_putendl("\n\nbefore 1st if\n\n");
	if (p->tri_vect == 3)
		w->trian[p->tri_i] = set_trian(w->trian[p->tri_i].p1, w->trian[p->tri_i].p2, w->trian[p->tri_i].p3);
	ft_putendl("\n\nbefore 2nd if\n\n");
	if (w->trian[p->tri_i].m.pattern == 1 && (w->trian[p->tri_i].pattern_type == 1
	|| w->trian[p->tri_i].pattern_type == 2))
	{
		//ft_putendl("\n\nin texture if\n\n");
		w->trian[p->tri_i].m.pattern_at = &pattern_at;
		//w->trian[p->tri_i].m.p.transform = identity_matrix();
		if (w->trian[p->tri_i].pattern_type == 1)
		{
			check.color_a = w->trian[p->tri_i].color_a;
			check.color_b = w->trian[p->tri_i].color_b;
			check.width = w->trian[p->tri_i].width;
			check.height = w->trian[p->tri_i].height;
			uv_checkers(check, &w->trian[p->tri_i].m.p);
		}
		else if (w->trian[p->tri_i].pattern_type == 2)
			stripe_pattern_shape(w->trian[p->tri_i].m.p.a, w->trian[p->tri_i].m.p.b,
			&w->trian[p->tri_i].m);
		if (w->trian[p->tri_i].m.tex == 1)
		{
			w->trian[p->tri_i].m.texturemap = texture_map(w->trian[p->tri_i].m.p,
			&planar_map);
			//printf("\n\nTRI TEXTURE IN MAKE TRI: %s\n\n", w->trian[0].texture);
			w->trian[p->tri_i].m.texture = SDL_LoadBMP(w->trian[p->tri_i].texture);
		}
	}
	//printf("\n\nTRI TEXTURE IN MAKE TRI: %s\n\n", w->trian[0].texture);
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