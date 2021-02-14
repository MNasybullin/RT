/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 16:37:31 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_putendl(char const *s)
{
	while (!s)
		return ;
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
	ft_putchar('\n');
}

int			ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s2 == '\0' && *s1)
		return (1);
	else
		return (*s1 - *s2);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int			ft_words(char const *s, char c)
{
	int		cu;
	int		i;

	i = 0;
	cu = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			cu++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (cu);
}

int			ft_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}
