/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 20:14:25 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 19:49:16 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		check_make_obj(char **tab)
{
	if (len_tab(tab) >= 2 && !(ft_strequ(tab[0], "-")) &&!(ft_strequ(tab[1], "object:")) &&
		!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "light:")) &&
		!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:")))
		return (1);
	return (0);
}

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
	ft_putendl("\n\ncheck_type\n\n");

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


void	making_obj(char **tab, t_data *p, t_world *w)
{
	int		i;

	i = 0;
	get_next_line(p->fd, &p->line);
	free_tab(tab);
	tab = NULL;
	tab = ft_strsplit(p->line, ' ');
	if (len_tab(tab) == 2)
	{
		p->tab = (char**)malloc(sizeof(char) * 2);
		p->tab[0] = ft_strdup(tab[0]);
		p->tab[1] = ft_strdup(tab[1]);
		while (!(ft_strcmp(p->tab[0], "type:")) && i < p->obj_n)
		{
			i++;
			check_type(p, w, p->tab);
		}
	}
	else
		exit(err_wrong_format());
}

int		check_is_obj(char **tab, t_data *p)
{
	if ((len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-"))
	&& !(ft_strcmp(tab[1], "object:"))) || !(strcmp_v2(p->line, "objects:")))
		return (1);
	return (0);
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
		if (!(strcmp_v2(p->line, "lights:")) || (len_tab(tab) == 2 && ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:")))
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
		if (!(strcmp_v2(p->line, "cameras:")) || (len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-")) && !(ft_strcmp(tab[1], "camera:"))))
		{
			//get_next_line(p->fd, &p->line);
			//tab = ft_strsplit(p->line, ' ');
			if (/*len_tab(tab) == 2 && */(ft_strcmp(tab[0], "-") && (ft_strcmp(tab[1], "camera:"))))
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
	//close(p->fd);
	return (0);
}