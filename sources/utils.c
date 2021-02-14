/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:57:41 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 14:11:31 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (1);
}

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int		strcmp_v2(char *s1, char *s2)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(s1, ' ');
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

int		valid_len(char ***tab, int len, t_data *p)
{
	if ((len_tab(*tab)) == len)
		return (1);
	while ((len_tab(*tab)) != len)
	{
		free_tab(*tab);
		get_next_line(p->fd, &p->line);
		*tab = ft_strsplit(p->line, ' ');
		if ((len_tab(*tab)) == len)
			return (1);
	}
	return (0);
}

void	skip_empty_lines(t_data *p)
{
	while ((get_next_line(p->fd, &p->line)) && !(ft_strcmp(p->line, "\n")))
		get_next_line(p->fd, &p->line);
}
