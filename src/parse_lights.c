/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:03:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/03 21:58:40 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	lights_pos(t_data *p)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	tab4 = NULL;
	if (len_tab(p->tab) == 9)
	{
		tab1 = ft_strsplit(p->tab[2], ',');
		tab2 = ft_strsplit(p->tab[4], ',');
		tab3 = ft_strsplit(p->tab[6], ',');
		tab4 = ft_strsplit(p->tab[8], '}');
		p->h[p->light_i].a = ft_strtodbl(tab1[0]);
		p->h[p->light_i].b = ft_strtodbl(tab2[0]);
		p->h[p->light_i].c = ft_strtodbl(tab3[0]);
		p->h[p->light_i].w = ft_strtodbl(tab4[0]);
	}
	free_split_tab4(&tab1, &tab2, &tab3, &tab4);
}

void	lights_color(t_data *p)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	init_3_tabs(&tab1, &tab2, &tab3);
	if (len_tab(p->tab) == 7)
	{
		tab1 = ft_strsplit(p->tab[2], ',');
		tab2 = ft_strsplit(p->tab[4], ',');
		tab3 = ft_strsplit(p->tab[6], '}');
		p->h[p->light_i].r = ft_strtodbl(tab1[0]);
		p->h[p->light_i].g = ft_strtodbl(tab2[0]);
		p->h[p->light_i].bl = ft_strtodbl(tab3[0]);
	}
	free_split_tab(tab1, tab2, tab3);
}

void	lights_vec(t_data *p, int type)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	init_4_tabs(&tab1, &tab2, &tab3, &tab4);
	if (len_tab(p->tab) == 9)
	{
		tab1 = ft_strsplit(p->tab[2], ',');
		tab2 = ft_strsplit(p->tab[4], ',');
		tab3 = ft_strsplit(p->tab[6], ',');
		tab4 = ft_strsplit(p->tab[8], '}');
		if (type == 1)
			p->h[p->light_i].corner = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		if (type == 2)
			p->h[p->light_i].v1 = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
		if (type == 3)
			p->h[p->light_i].v2 = set_v_p(ft_strtodbl(tab1[0]),
			ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
	}
	free_split_tab4(&tab1, &tab2, &tab3, &tab4);
}

void	make_light(t_data *p)
{
	if (ft_strequ(p->tab[0], "type:") && len_tab(p->tab) == 2)
	{
		if (!(ft_strcmp(p->tab[1], "point")))
			p->h[p->light_i].type = 1;
		else if (ft_strequ(p->tab[1], "area"))
			p->h[p->light_i].type = 2;
	}
	if (ft_strequ(p->tab[0], "color:"))
		lights_color(p);
	if (ft_strequ(p->tab[0], "pos:"))
		lights_pos(p);
	if (ft_strequ(p->tab[0], "corner:"))
		lights_vec(p, 1);
	if (ft_strequ(p->tab[0], "v1:"))
		lights_vec(p, 2);
	if (ft_strequ(p->tab[0], "v2:"))
		lights_vec(p, 3);
	if (ft_strequ(p->tab[0], "usteps:"))
		p->h[p->light_i].usteps = ft_atoi(p->tab[1]);
	if (ft_strequ(p->tab[0], "vsteps:"))
		p->h[p->light_i].vsteps = ft_atoi(p->tab[1]);
}

void	parse_lights(t_data *p, t_world *w)
{
	w->ar_count += 0;
	p->h[p->light_i].usteps = 0;
	p->h[p->light_i].vsteps = 0;
	p->h[p->light_i].type = 0;
	while (get_next_line(p->fd, &p->line))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if (check_make_light(p->tab))
			make_light(p);
		else
			break ;
	}
	p->light_i++;
	free_tab(p->tab);
	p->tab = NULL;
}
