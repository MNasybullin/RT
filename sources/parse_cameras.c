/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:55:21 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 13:51:51 by sdiego           ###   ########.fr       */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:55:21 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 14:58:31 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	complex_params_camera(t_data *p, t_world *w, char **tab, int flag)
{
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**tab4;

	w->ar_count += 0;
	init_4_tabs(&tab1, &tab2, &tab3, &tab4);
	if (len_tab(tab) == 9)
	{
		tab1 = ft_strsplit(tab[2], ',');
		tab2 = ft_strsplit(tab[4], ',');
		tab3 = ft_strsplit(tab[6], ',');
		tab4 = ft_strsplit(tab[8], '}');
		w->from_x = ft_strtodbl(tab1[0]);
		w->from_y = ft_strtodbl(tab2[0]);
		w->from_z = ft_strtodbl(tab3[0]);
		w->to_x = ft_strtodbl(tab4[0]);
		if (flag == 1)
			p->c.from = set_v_p(w->from_x, w->from_y, w->from_z, w->to_x);
		if (flag == 2)
			p->c.to = set_v_p(w->from_x, w->from_y, w->from_z, w->to_x);
		if (flag == 3)
			p->c.up = set_v_p(w->from_x, w->from_y, w->from_z, w->to_x);
	}
}

void	camera_parsing(t_data *p, t_world *w)
{
	if (ft_strequ(p->tab[0], "fov:") && len_tab(p->tab) == 2)
		p->c.fov = ft_strtodbl(p->tab[1]);
	if (ft_strequ(p->tab[0], "from:") && len_tab(p->tab) == 9)
		complex_params_camera(p, w, p->tab, 1);
	if (ft_strequ(p->tab[0], "to:") && len_tab(p->tab) == 9)
		complex_params_camera(p, w, p->tab, 2);
	if (ft_strequ(p->tab[0], "up:") && len_tab(p->tab) == 9)
		complex_params_camera(p, w, p->tab, 3);
}

void	parse_cameras(t_data *p, t_world *w)
{
	t_camera	c;

	while (get_next_line(p->fd, &p->line))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if (!(ft_strequ(p->tab[0], "objects:")) && !(ft_strequ(p->tab[0], "-"))
		&& !(ft_strequ(p->tab[1], "object:")) &&
		!(ft_strequ(p->tab[0], "lights:")) && !(ft_strequ(p->tab[0], "...")) &&
		(!(ft_strequ(p->tab[0], "-")) && !(ft_strequ(p->tab[1], "light:"))))
			camera_parsing(p, w);
		else
			break ;
	}
	c = camera(WIN_W, WIN_H, p->c.fov);
	c.transform = view_transform(p->c.from, p->c.to, p->c.up);
	w->c = c;
	p->tab = NULL;
}
