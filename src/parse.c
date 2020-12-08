/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 20:14:25 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/08 20:07:03 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

char	**check_type(t_data *p, t_world *w, char **tab)
{
	if (!(ft_strcmp(tab[1], "plane")))
		p->tab = make_plane(p, w, tab);
	if (!(ft_strcmp(tab[1], "sphere")))
		p->tab = make_sphere(p, w, tab);
	if (!(ft_strcmp(tab[1], "cone")))
		p->tab = make_cone(p, w, tab);
	if (!(ft_strcmp(tab[1], "cylinder")))
		p->tab = make_cyl(p, w, tab);
	if (!(ft_strcmp(tab[1], "cube")))
		make_cube(p, w, tab);
	if (!(ft_strcmp(tab[1], "triangle")))
		make_tri(p, w, tab);
	return (p->tab);
}

void	making_light(t_data *p, t_world *w, char **tab)
{
	if (!(strcmp_v2(p->line, "lights:")))
	{
		get_next_line(p->fd, &p->line);
		tab = ft_strsplit(p->line, ' ');
	}
	if (len_tab(tab) == 2 && (ft_strcmp(tab[0], "-") &&
	(ft_strcmp(tab[1], "light:"))))
	{
		get_next_line(p->fd, &p->line);
		tab = ft_strsplit(p->line, ' ');
	}
	if (len_tab(tab) == 2 && ft_strequ(tab[0], "-") &&
	ft_strequ(tab[1], "light:"))
	{
		p->tab = NULL;
		parse_lights(p, w);
	}
}

void	making_camera(t_data *p, t_world *w, char **tab)
{
	if (len_tab(tab) == 2 && (ft_strcmp(tab[0], "-") &&
	(ft_strcmp(tab[1], "camera:"))))
	{
		get_next_line(p->fd, &p->line);
		tab = ft_strsplit(p->line, ' ');
	}
	if (ft_strequ(tab[0], "-") && ft_strequ(tab[1], "camera:"))
	{
		p->cam_num++;
		p->tab = NULL;
		parse_cameras(p, w);
	}
}

void	reading(t_data *p, t_world *w, char *file)
{
	start_count_obj(p, w);
	p->fd = open(file, O_RDONLY);
	start_count_lights(p, w);
	p->fd = open(file, O_RDONLY);
	get_next_line(p->fd, &p->line);
	get_next_line(p->fd, &p->line);
}

int		read_file(char *file, t_data *p, t_world *w)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	init_parse(p, w);
	if ((p->fd = open(file, O_RDONLY)) == -1)
		exit(err_invalid_file());
	get_next_line(p->fd, &p->line);
	if ((ft_strcmp(p->line, "---")))
		exit(err_invalid_file());
	reading(p, w, file);
	while ((get_next_line(p->fd, &p->line)))
	{
		if (!p->line)
			continue ;
		tab = ft_strsplit(p->line, ' ');
		if (check_is_obj(tab, p))
			making_obj(tab, p, w);
		if (check_is_light(tab, p))
			making_light(p, w, tab);
		if (check_is_camera(tab, p))
			making_camera(p, w, tab);
	}
	write_lights(p, w);
	p->light_i = 0;
	return (0);
}
