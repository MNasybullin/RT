/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 16:19:01 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char		*ft_strchr(const char *str, int ch)
{
	unsigned char	k;
	char			*new;

	k = (unsigned char)ch;
	new = (char *)str;
	while (*new)
	{
		if (*new == ch)
			return (new);
		else
			new++;
	}
	if (k == '\0')
		return (new);
	else
		return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char *)mem(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

int			ft_atoi(const char *str)
{
	static unsigned long		i;
	unsigned long long			num;
	static int					mod;

	i = 0;
	num = 0;
	if (!str)
		return (0);
	while (*(str + i) == '\n' || *(str + i) == '\t'  \
	|| *(str + i) == '\r' || *(str + i) == '\v' \
	|| *(str + i) == '\f' || *(str + i) == ' ')
		i++;
	mod = (*(str + i) == '-') ? -1 : 1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		num = (unsigned long long)(num * 10 + (*(str + i++) - '0'));
		if (num > (long long)MAX_LONG_LONG && mod == 1)
			return (-1);
		if (num > (long long)MAX_LONG_LONG && mod == -1)
			return (0);
	}
	return ((int)(num * mod));
}

char		*ft_strdup(const char *src)
{
	int		i;
	char	*c;

	i = 0;
	if (!(c = (char *)mem(ft_strlen(src) + 1)) \
	|| ft_strlen(src) > (ft_strlen(src) + 1))
		return (NULL);
	i = 0;
	while (src[i])
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
