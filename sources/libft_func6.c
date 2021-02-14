/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 16:39:42 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_strtodbl_dot(char *s)
{
	int		dot;
	int		i;

	dot = 0;
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '.')
			dot++;
	return (dot);
}

double		ft_strtodbl(char *s)
{
	char	**tab;
	double	x;
	double	y;
	int		len;

	x = 0.0;
	y = 0;
	ft_strtodbl_dot(s);
	if (!ft_strtodbl_dot(s))
		return ((double)ft_atoi(s));
	tab = ft_strsplit(s, '.');
	check_tab_len(tab);
	x = (double)ft_atoi(tab[0]);
	y = (double)ft_atoi(tab[1]);
	len = ft_strlen(tab[1]);
	while (--len > -1)
		y /= 10;
	if (s[0] == '-')
		x -= y;
	else
		x += y;
	free_tab(tab);
	return (x);
}
