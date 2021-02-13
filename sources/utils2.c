/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:27:42 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/13 22:03:17 by mgalt            ###   ########.fr       */
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

void	cycle_triangle(t_data *p, t_world *w)
{
	while ((get_next_line(p->fd, &p->line)))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(p->tab)))
			make_obj_tri(p, w, p->tab);
		else
			break ;
	}
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


void	cycle_cube(t_data *p, t_world *w)
{
	while ((get_next_line(p->fd, &p->line)))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(p->tab)))
			make_obj_cube(p, w, p->tab);
		else
			break ;
	}
}
