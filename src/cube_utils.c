/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:15:32 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/12 13:51:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	make_tex_cube(t_data *p, t_world *w)
{
	if (w->cub[p->cube_i].tex_num == 6)
	{
		w->cub[p->cube_i].m.p.cube_texture[0] =
		SDL_LoadBMP(w->cub[p->cube_i].right);
		w->cub[p->cube_i].m.p.cube_texture[1] =
		SDL_LoadBMP(w->cub[p->cube_i].left);
		w->cub[p->cube_i].m.p.cube_texture[2] =
		SDL_LoadBMP(w->cub[p->cube_i].up);
		w->cub[p->cube_i].m.p.cube_texture[3] =
		SDL_LoadBMP(w->cub[p->cube_i].down);
		w->cub[p->cube_i].m.p.cube_texture[4] =
		SDL_LoadBMP(w->cub[p->cube_i].front);
		w->cub[p->cube_i].m.p.cube_texture[5] =
		SDL_LoadBMP(w->cub[p->cube_i].back);
	}
	else
		exit(err_num_tex());
}

void	make_obj_cube_4(t_data *p, t_world *w, char **tab, char *tmp)
{
	if (!(ft_strcmp(tab[0], "lower_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].down = ft_strdup(tmp);
		free(tmp);
	}
	if (!(ft_strcmp(tab[0], "front_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].front = ft_strdup(tmp);
		free(tmp);
	}
	if (!(ft_strcmp(tab[0], "back_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].back = ft_strdup(tmp);
		free(tmp);
	}
	if (!(ft_strcmp(tab[0], "pattern_color_a:")))
		pattern_color_cube(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "pattern_color_b:")))
		pattern_color_cube(p, w, tab, 2);
}

void	make_obj_cube_3(t_data *p, t_world *w, char **tab, char *tmp)
{
	if (!(ft_strcmp(tab[0], "tex:")))
		texture_cube(tab, p, w);
	if (!(ft_strcmp(tab[0], "right_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].right = ft_strdup(tmp);
	}
	if (!(ft_strcmp(tab[0], "left_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].left = ft_strdup(tmp);
		free(tmp);
	}
	if (!(ft_strcmp(tab[0], "upper_side:")) && len_tab(tab) == 2)
	{
		w->cub[p->cube_i].tex_num++;
		tmp = remove_quotes(tab[1]);
		w->cub[p->cube_i].up = ft_strdup(tmp);
		free(tmp);
	}
}

void	make_obj_cube_2(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[0], "obj_translation:")) ||
	!(ft_strcmp(tab[0], "m_translation:")))
		complex_params_cube(p, w, tab, 1);
	if (!(ft_strcmp(tab[0], "color:")))
		complex_params_cube(p, w, tab, 2);
	if (!(ft_strcmp(tab[0], "obj_rotation:")) || !(ft_strcmp(tab[0],
	"m_rotation:")))
		complex_params_cube(p, w, tab, 3);
	if (!(ft_strcmp(tab[0], "obj_scaling:")) || !(ft_strcmp(tab[0],
	"m_scaling:")))
		complex_params_cube(p, w, tab, 4);
	if (!(ft_strcmp(tab[0], "pattern_type:")))
	{
		if (!(ft_strcmp(tab[1], "checker")))
			w->cub[p->cube_i].pattern_type = 1;
		if (!(ft_strcmp(tab[1], "stripe")))
			w->cub[p->cube_i].pattern_type = 2;
		if (!(ft_strcmp(tab[1], "gradient")))
			w->cub[p->cube_i].pattern_type = 3;
		if (!(ft_strcmp(tab[1], "ring")))
			w->cub[p->cube_i].pattern_type = 4;
	}
	if (!(ft_strcmp(tab[0], "pattern:")) && !(ft_strcmp(tab[1], "1")))
		w->cub[p->cube_i].m.pattern = 1;
}

void	make_obj_cube(t_data *p, t_world *w, char **tab)
{
	char	*tmp;

	tmp = NULL;
	if (!(ft_strcmp(tab[0], "specular:")))
		w->cub[p->cube_i].m.specular = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "reflective:")))
		w->cub[p->cube_i].m.reflective = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "ambient:")))
		w->cub[p->cube_i].m.ambient = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "diffuse:")))
		w->cub[p->cube_i].m.diffuse = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shininess:")))
		w->cub[p->cube_i].m.shininess = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "transparency:")))
		w->cub[p->cube_i].m.transparency = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "refractive_index:")))
		w->cub[p->cube_i].m.refractive_index = ft_strtodbl(tab[1]);
	if (!(ft_strcmp(tab[0], "shadow:")))
		w->cub[p->cube_i].m.shadow = ft_atoi(tab[1]);
	make_obj_cube_2(p, w, tab);
	make_obj_cube_3(p, w, tab, tmp);
	make_obj_cube_4(p, w, tab, tmp);
}
