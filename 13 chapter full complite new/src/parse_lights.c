/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:03:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 18:15:17 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		p->h.a = ft_strtodbl(tab1[0]);
		p->h.b = ft_strtodbl(tab2[0]);
		p->h.c = ft_strtodbl(tab3[0]);
		p->h.w = ft_strtodbl(tab4[0]);
	}
	free_tab(tab1);
	free_tab(tab2);
	free_tab(tab3);
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
}

void	lights_color(t_data *p)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;

	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	if (len_tab(p->tab) == 7)
	{
		tab1 = ft_strsplit(p->tab[2], ',');
		tab2 = ft_strsplit(p->tab[4], ',');
		tab3 = ft_strsplit(p->tab[6], '}');
		p->h.r = ft_strtodbl(tab1[0]);
		p->h.g = ft_strtodbl(tab2[0]);
		p->h.bl = ft_strtodbl(tab3[0]);
	}
	free_tab(tab1);
	free_tab(tab2);
	free_tab(tab3);
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
}

void    parse_lights(t_data *p, t_world *w)
{
	while (get_next_line(p->fd, &p->line))
	{
		//ft_putendl("while in parse lights");
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if (!(ft_strequ(p->tab[0], "objects:")) && !(ft_strequ(p->tab[0], "-")) && !(ft_strequ(p->tab[1], "object:")) &&
		!(ft_strequ(p->tab[0], "-")) && !(ft_strequ(p->tab[1], "lights:")) && !(ft_strequ(p->tab[0], "cameras:")))
		{
			if (ft_strequ(p->tab[0], "type:") && len_tab(p->tab) == 2)
			{
				if (ft_strequ(p->tab[1], "point"))
					p->h.type = 'p';
				else if (ft_strequ(p->tab[1], "direction"))
					p->h.type = 'd';
			}	
			if (ft_strequ(p->tab[0], "color:"))
				lights_color(p);
			if (ft_strequ(p->tab[0], "pos:"))
				lights_pos(p);
		}
		else
			break ;
	}
	printf("LIGHT:\n---\n%f %f %f %f %f %f %f\n", p->h.r, p->h.g, p->h.bl, p->h.a, p->h.b, p->h.c, p->h.w);
	if (p->h.type == 'p')
		w->light = point_light(color(p->h.r, p->h.g, p->h.bl), set_v_p(p->h.a, p->h.b, p->h.c, p->h.w));
	//printf("LIGHT:\n---\n%f %f %f %f %f %f %f\n", p->h.r, p->h.g, p->h.bl, p->h.a, p->h.b, p->h.c, p->h.w);
	//free_tab(p->tab);
	p->tab = NULL;
}