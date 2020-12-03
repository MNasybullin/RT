/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:56:24 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/03 21:58:36 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	free_split_tab4(char ***tab1, char ***tab2, char ***tab3, char ***tab4)
{
	free_tab(*tab1);
	free_tab(*tab2);
	free_tab(*tab3);
	free_tab(*tab4);
	*tab1 = NULL;
	*tab2 = NULL;
	*tab3 = NULL;
	*tab4 = NULL;
}

void	init_4_tabs(char ***tab1, char ***tab2, char ***tab3, char ***tab4)
{
	*tab1 = NULL;
	*tab2 = NULL;
	*tab3 = NULL;
	*tab4 = NULL;
}

void	init_3_tabs(char ***tab1, char ***tab2, char ***tab3)
{
	*tab1 = NULL;
	*tab2 = NULL;
	*tab3 = NULL;
}

void	free_split_tab(char **tab1, char **tab2, char **tab3)
{
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
	while (i < p->lights_num)
	{
		if (p->h[i].type == 1)
			w->light[i] = point_light(color(p->h[i].r, p->h[i].g, p->h[i].bl),
			set_v_p(p->h[i].a, p->h[i].b, p->h[i].c, p->h[i].w));
		if (p->h[p->light_i].type == 2)
			w->light[i] = area_light(p->h[i].corner, p->h[i].v1,
			p->h[i].usteps, p->h[i].v2, p->h[i].vsteps, color(p->h[i].r,
			p->h[i].g, p->h[i].bl));
		i++;
	}
}
