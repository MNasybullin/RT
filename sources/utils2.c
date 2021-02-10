/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:27:42 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/03 22:07:57 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_format(char *file)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	i = len - 4;
	if (file[i] == '.' && file[i + 1] == 'y' &&
	file[i + 2] == 'm' && file[i + 3] == 'l')
		return (1);
	else
		return(0);
}

void	help_counting(t_data *p, char **tab)
{
	if (!(ft_strcmp(tab[1], "plane")))
		p->pl_num++;
	if (!(ft_strcmp(tab[1], "sphere")))
		p->sp_num++;
	if (!(ft_strcmp(tab[1], "cone")))
		p->cone_num++;
	if (!(ft_strcmp(tab[1], "cylinder")))
		p->cyl_num++;
	if (!(ft_strcmp(tab[1], "cube")))
		p->cube_num++;
	if (!(ft_strcmp(tab[1], "triangle")))
		p->tri_num++;
}

char	*remove_quotes(char *s1)
{
    char	**res;

	res = NULL;
	res = ft_strsplit(s1, 34);
	if (res)
		return (res[0]);
	return (NULL);
}