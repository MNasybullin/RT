/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:57:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/24 18:13:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		strcmp_v2(char *s1, char *s2)
{
	char	**tab;

	tab = NULL;
	//tab[0] = (unsigned char *)tab[0];
	//s2 = (unsigned char *)s2;
	tab = ft_strsplit(tab[0], ' ');
	if (tab)
	{
		while (*tab[0] && *s2 && *tab[0] == *s2)
		{
			tab[0]++;
			s2++;
		}
		if (*s2 == '\0' && *tab[0])
			return (1);
		else
			return (*tab[0] - *s2);
	}
	else
		exit(err_mem_alloc());
	return (0);
}
