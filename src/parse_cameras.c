/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:55:21 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 22:00:30 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

// don't forget to count cameras!

void	complex_params_camera(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	w->ar_count += 0;
	tab1 = NULL;
	tab2 = NULL;
	tab3 = NULL;
	tab4 = NULL;
	tab1 = ft_strsplit(tab[2], ',');
	tab2 = ft_strsplit(tab[4], ',');
	tab3 = ft_strsplit(tab[6], ',');
	tab4 = ft_strsplit(tab[8], '}');
	if (flag == 1) // from
		p->c.from = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
	if (flag == 2) // to
		p->c.to = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
	if (flag == 3) // up
		p->c.up = set_v_p(ft_strtodbl(tab1[0]), ft_strtodbl(tab2[0]), ft_strtodbl(tab3[0]), ft_strtodbl(tab4[0]));
	// добавить проверку есть ли эти векторы
}

void    parse_cameras(t_data *p, t_world *w)
{
	t_camera	c;

	//ft_putendl("parse cameras");
	
    while (get_next_line(p->fd, &p->line))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		//printf("\n\n tab[0] %s, tab[1] %s\n", p->tab[0], p->tab[1]);
		if (!(ft_strequ(p->tab[0], "objects:")) && !(ft_strequ(p->tab[0], "-")) && !(ft_strequ(p->tab[1], "object:")) &&
		/*!(ft_strequ(p->tab[0], "-")) && */!(ft_strequ(p->tab[0], "lights:")) && !(ft_strequ(p->tab[0], "...")) &&
		(!(ft_strequ(p->tab[0], "-")) && !(ft_strequ(p->tab[1], "light:"))))
		{
			if (ft_strequ(p->tab[0], "fov:") && len_tab(p->tab) == 2)
			{
				ft_putendl("\n\n if fov && len tab == 2\n");
				p->c.fov = ft_strtodbl(p->tab[1]);
			}
			if (ft_strequ(p->tab[0], "from:") && len_tab(p->tab) == 9)
				complex_params_camera(p, w, p->tab, 1);
			if (ft_strequ(p->tab[0], "to:") && len_tab(p->tab) == 9)
				complex_params_camera(p, w, p->tab, 2);
			if (ft_strequ(p->tab[0], "up:") && len_tab(p->tab) == 9)
				complex_params_camera(p, w, p->tab, 3);
		}
		else
			break ;
	}
	printf("\n\n\nLINE IN THE END OF PARSE CAMERAS: %s\n\n\n", p->line);
	c = camera(WIN_W, WIN_H, p->c.fov);
	c.transform = view_transform(p->c.from, p->c.to, p->c.up);
	w->c = c;
	//free_tab(p->tab);
	p->tab = NULL;
	printf("CAMERAAAA: %d %d %f\n", w->c.hsize, w->c.vsize, w->c.fov);
}