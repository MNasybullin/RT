/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:27:19 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 14:09:02 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	alloc_obj_memory(t_data *p, t_world *w)
{
	if (p->pl_num)
		w->pl = (t_plane*)mem(sizeof(t_plane) * p->pl_num);
	if (p->sp_num)
		w->s = (t_sp*)mem(sizeof(t_sp) * p->sp_num);
	if (p->cone_num)
		w->cone = (t_cone*)mem(sizeof(t_cone) * p->cone_num);
	if (p->cyl_num)
		w->cyl = (t_cyl*)mem(sizeof(t_cyl) * p->cyl_num);
	if (p->cube_num)
		w->cub = (t_cube*)mem(sizeof(t_cube) * p->cube_num);
	if (p->tri_num)
		w->trian = (t_trian*)mem(sizeof(t_trian) * p->tri_num);
	w->obj_ar = (t_shape*)mem(sizeof(t_shape) * p->obj_n);
}

void	count_objects(t_data *p, char *line)
{
	char	**tab;
	int		len;

	len = 0;
	get_next_line(p->fd, &line);
	tab = NULL;
	while ((get_next_line(p->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = len_tab(tab);
		if (len == 2)
		{
			if (!(ft_strcmp(tab[0], "type:")))
				help_counting(p, tab);
			free_tab(tab);
			tab = NULL;
		}
	}
	p->obj_n = p->pl_num + p->sp_num + p->cone_num + p->cyl_num
	+ p->cube_num + p->tri_num;
	close(p->fd);
}

void	start_count_obj(t_data *p, t_world *w)
{
	char	**tab;

	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 1)
		{
			if (!(ft_strcmp(tab[0], "objects:")))
			{
				count_objects(p, p->line);
				alloc_obj_memory(p, w);
				break ;
			}
		}
		else if (len_tab(tab) == 0)
			exit(err_wrong_format());
		free_tab(tab);
		tab = NULL;
	}
}

void	count_lights(t_data *p, char *line)
{
	char	**tab;
	int		len;

	len = 0;
	get_next_line(p->fd, &line);
	tab = NULL;
	while ((get_next_line(p->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = len_tab(tab);
		if (len == 2)
		{
			if (!(ft_strcmp(tab[0], "type:")) && (!(ft_strcmp(tab[1], "point"))
			|| !(ft_strcmp(tab[1], "area"))))
				p->lights_num++;
			free_tab(tab);
			tab = NULL;
		}
	}
	close(p->fd);
}

void	start_count_lights(t_data *p, t_world *w)
{
	char	**tab;

	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 1)
		{
			if (!(ft_strcmp(tab[0], "lights:")))
			{
				count_lights(p, p->line);
				break ;
			}
		}
		free_tab(tab);
		tab = NULL;
	}
	if (p->lights_num)
	{
		w->light_obj = p->lights_num;
		w->light = (t_light*)mem(sizeof(t_light) * p->lights_num);
		p->h = (t_forlight*)mem(sizeof(t_forlight) * p->lights_num);
	}
}
