/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:51:25 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/24 18:38:19 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

void	making_lights(char **tab, t_data *p, t_world *w)
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
		while (!(ft_strcmp(p->tab[0], "type:")) && i < p->lights_num)
		{
			i++;
			parse_lights(p, w);
		}
	}
	else
		exit(err_wrong_format());
}
