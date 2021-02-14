/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:27:42 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 12:52:57 by mgalt            ###   ########.fr       */
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

void	find_path(t_data *p)
{
	int		fd;
	int		len;
	char	**tab;

	fd = ft_open_file(p->file);
	len = 0;
	tab = NULL;
	while ((get_next_line(p->fd, &p->line)) > 0)
	{
		tab = ft_strsplit(p->line, ' ');
		len = len_tab(tab);
		if (len == 2)
		{
			if (!(ft_strcmp(tab[0], "path:")))
				p->path = ft_strdup(remove_quotes(tab[1]));
			free_tab(tab);
			tab = NULL;
		}
	}
	close(fd);
	get_obj_triangle_count(p->path, p);
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
	if (!(ft_strcmp(tab[1], "obj")))
		find_path(p);
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