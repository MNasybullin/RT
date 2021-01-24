/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:59:20 by mgalt             #+#    #+#             */
/*   Updated: 2021/01/24 18:13:12 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		final_if_cube(char **tab)
{
	//if ((!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "lights:"))) &&
	//(!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:"))))
	if (len_tab(tab) >= 2 && (!(ft_strequ(tab[0], "lights:"))
	&& !(ft_strequ(tab[1], "light:"))) && (!(ft_strequ(tab[0], "cameras:"))
	&& !(ft_strequ(tab[1], "camera:"))))
		return (1);
	return (0);
}
