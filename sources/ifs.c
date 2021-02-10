/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:15:17 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/24 18:37:43 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_is_obj(char **tab, t_data *p)
{
	if ((len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-"))
	&& !(ft_strcmp(tab[1], "object:"))) || !(strcmp_v2(p->line, "objects:")))
		return (1);
	return (0);
}

int		check_make_obj(char **tab)
{
	if (len_tab(tab) >= 2 && !(ft_strequ(tab[0], "-")) && !(ft_strequ(tab[1],
	"object:")) && !(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1],
	"light:")) && !(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1],
	"camera:")))
		return (1);
	return (0);
}

int		check_make_light(char **tab)
{
	if (!(ft_strequ(tab[0], "objects:")) && !(ft_strequ(tab[0], "cameras:"))
	&& (len_tab(tab) >= 2 && (!(ft_strequ(tab[0], "-")) &&
	!(ft_strequ(tab[1], "object:"))) && (!(ft_strequ(tab[0], "-")) &&
	!(ft_strequ(tab[1], "light:")))))
		return (1);
	return (0);
}

int		check_is_light(char **tab, t_data *p)
{
	if (!(strcmp_v2(p->line, "lights:")) ||
	(len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-")) &&
	!(ft_strcmp(tab[1], "light:"))))
		return (1);
	return (0);
}

int		check_is_camera(char **tab, t_data *p)
{
	if (!(strcmp_v2(p->line, "cameras:")) ||
	(len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-")) &&
	!(ft_strcmp(tab[1], "camera:"))))
		return (1);
	return (0);
}
