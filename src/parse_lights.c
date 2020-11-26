/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:03:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 22:00:03 by mgalt            ###   ########.fr       */
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
		p->h[p->light_i].r = ft_strtodbl(tab1[0]);
		p->h[p->light_i].g = ft_strtodbl(tab2[0]);
		p->h[p->light_i].bl = ft_strtodbl(tab3[0]);
	}
	free_tab(tab1);
	free_tab(tab2);
	free_tab(tab3);
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
}

void	write_lights(t_data *p, t_world *w)
{
	int		i;

	i = 0;
	//if (p->h[i].type == 'p')
	//{
	while (i < p->lights_num)
	{
		w->light[i] = point_light(color(p->h[i].r, p->h[i].g, p->h[i].bl), set_v_p(p->h[i].a, p->h[i].b, p->h[i].c, p->h[i].w));
		i++;
	}
	//}
}

void    parse_lights(t_data *p, t_world *w)
{
	//int		i;

	//i = 0;
	w->ar_count += 0;
	while (get_next_line(p->fd, &p->line))
	{
		//ft_putendl("while in parse lights");
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if (check_make_light(p->tab))
		{
			if (ft_strequ(p->tab[0], "type:") && len_tab(p->tab) == 2)
			{
				if (ft_strequ(p->tab[1], "point"))
					p->h[p->light_i].type = 'p';
				else if (ft_strequ(p->tab[1], "direction"))
					p->h[p->light_i].type = 'd';
			}	
			if (ft_strequ(p->tab[0], "color:"))
				lights_color(p);
			if (ft_strequ(p->tab[0], "pos:"))
				lights_pos(p);
		}
		else
			break ;
	}
	p->light_i++;
	//printf("LIGHT:\n---\n%f %f %f %f %f %f %f\n", p->h[p->light_i].r, p->h[p->light_i].g, p->h[p->light_i].bl, p->h[p->light_i].a, p->h[p->light_i].b, p->h[p->light_i].c, p->h[p->light_i].w);
	/*if (p->h[p->light_i].type == 'p')
	{
		while (i < p->lights_num)
		{
			w->light[i] = point_light(color(p->h[i].r, p->h[i].g, p->h[i].bl), set_v_p(p->h[i].a, p->h[i].b, p->h[i].c, p->h[i].w));
			i++;
		}
	}*/
	//printf("LIGHT:\n---\n%f %f %f %f %f %f %f\n", p->h.r, p->h.g, p->h.bl, p->h.a, p->h.b, p->h.c, p->h.w);
	free_tab(p->tab);
	p->tab = NULL;
}