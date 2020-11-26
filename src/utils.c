/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:57:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 19:37:28 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
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

int		valid_len(char ***tab, int len, t_data *p)
{
	//ft_putendl("in valid len");
	//printf("Len tab is %d\n\n", len_tab(*tab));
	if ((len_tab(*tab)) == len)
			return (1);
	while ((len_tab(*tab)) != len)
	{
		free_tab(*tab);
		get_next_line(p->fd, &p->line);
		//if (len_tab(*tab) == len)
		//	return(1);
		//if (get_next_line(p->fd, &p->line) == -1)
		//	return(0);
		*tab = ft_strsplit(p->line, ' ');
		//printf("tab len: %d\n", len_tab(*tab));
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

void	print_parameters(t_world *w)
{
	ft_putendl("\nprint parameters\n");
	printf("plane1:\n---\nspec: %.1f\nreflection: %.1f\n\n", w->pl[0].m.specular, w->pl[0].m.reflective);
	printf("plane2:\n---\nspec: %.1f\nambient: %.1f\n\n", w->pl[1].m.specular, w->pl[1].m.ambient);
	printf("plane3:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[2].m.specular, w->pl[2].m.reflective, w->pl[2].m.diffuse, w->pl[2].m.ambient);
	printf("plane4:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[3].m.specular, w->pl[3].m.reflective, w->pl[3].m.diffuse, w->pl[3].m.ambient);
	printf("plane5:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[4].m.specular, w->pl[4].m.reflective, w->pl[4].m.diffuse, w->pl[4].m.ambient);
	printf("plane6:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[5].m.specular, w->pl[5].m.reflective, w->pl[5].m.diffuse, w->pl[5].m.ambient);
	
	printf("sphere1:\n---\nshine: %.1f\n\n", w->s[0].m.shininess);
	printf("sphere2:\n---\nshine: %.1f\n\n", w->s[1].m.shininess);
	printf("sphere3:\n---\nshine: %.1f\n\n", w->s[2].m.shininess);
	printf("sphere4:\n---\nshine: %.1f\n\n", w->s[3].m.shininess);
	printf("sphere5:\n---\nspec: %.1f\nshine: %.1f\n\n", w->s[4].m.specular, w->s[4].m.shininess);
	printf("sphere6:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\nshine: %.1f\ntransparency: %.1f\nrefract: %.1f\n\n", w->s[5].m.specular, w->s[5].m.reflective, w->s[5].m.diffuse, w->s[5].m.ambient, w->s[5].m.shininess, w->s[5].m.transparency,w->s[5].m.refractive_index);
	printf("sphere7:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\nshine: %.1f\ntransparency: %.1f\nrefract: %.1f\n\n", w->s[6].m.specular, w->s[6].m.reflective, w->s[6].m.diffuse, w->s[6].m.ambient, w->s[6].m.shininess, w->s[6].m.transparency,w->s[6].m.refractive_index);
}
