/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 20:14:25 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 22:04:59 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		check_format(char *file)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	i = len - 4;
	if (file[i] == '.' && file[i + 1] == 'y' &&
	file[i + 2] == 'm' && file[i + 3] == 'l')
		return (1);
	else
		return(0);
}

char	**check_type(t_data *p, t_world *w, char **tab)
{
	//ft_putendl("\n\ncheck_type\n\n");

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

int		read_file(char *file, t_data *p, t_world *w)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	init_parse(p, w);
	if ((p->fd = open(file, O_RDONLY)) == -1)
		exit (err_invalid_file());
	get_next_line(p->fd, &p->line);
	if ((ft_strcmp(p->line, "---")))
		exit (err_invalid_file());
	start_count_obj(p, w);
	p->fd = open(file, O_RDONLY);
	start_count_lights(p, w);
	p->fd = open(file, O_RDONLY);
	get_next_line(p->fd, &p->line);
	get_next_line(p->fd, &p->line);
	while ((get_next_line(p->fd, &p->line)))
	{
		printf("\n\nline in beginning of while: %s\n\n", p->line);
		tab = ft_strsplit(p->line, ' ');
		if (check_is_obj(tab, p))
			making_obj(tab, p, w);
		if (check_is_light(tab, p))
		{
			if (!(strcmp_v2(p->line, "lights:")))
			{
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (len_tab(tab) == 2 && (ft_strcmp(tab[0], "-") && (ft_strcmp(tab[1], "light:"))))
			{
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (len_tab(tab) == 2 && ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:"))
			{
				p->tab = NULL;
				parse_lights(p, w);
			}
		}
		p->tab = NULL;
		if (check_is_camera(tab, p))
		{
			//get_next_line(p->fd, &p->line);
			//tab = ft_strsplit(p->line, ' ');
			if (len_tab(tab) == 2 && (ft_strcmp(tab[0], "-") &&
			(ft_strcmp(tab[1], "camera:"))))
			{
				//ft_putendl("\nin if !(ft_strequ(tab[0], -) && !(ft_strequ(tab[1], light:))\n");
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (ft_strequ(tab[0], "-") && ft_strequ(tab[1], "camera:"))
			{
				p->cam_num++;
				p->tab = NULL;
				//get_next_line(p->fd, &p->line);
				parse_cameras(p, w);
			}
		}
	}
	write_lights(p, w);
	p->light_i = 0;
	printf("LIGHT:\n---\n%f %f %f %f %f %f %f\n", p->h[p->light_i].r, p->h[p->light_i].g, p->h[p->light_i].bl, p->h[p->light_i].a, p->h[p->light_i].b, p->h[p->light_i].c, p->h[p->light_i].w);
	//close(p->fd);
	return (0);
}