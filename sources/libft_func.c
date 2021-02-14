/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 16:17:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*new;

	i = 0;
	new = (char *)s;
	while (n > i)
	{
		new[i] = '\0';
		i++;
	}
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		*ft_memcpy(void *dest, const void *source, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)source;
	if (!source && !dest)
		return (NULL);
	i = 0;
	if (n <= 0)
		return (str1);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dest);
}

void		*ft_memalloc(size_t size)
{
	void	*new;

	if (size == 0)
		return (NULL);
	new = mem(size);
	if (!new)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}

char		*ft_strnew(size_t size)
{
	char	*new;

	if ((size + 1) < size)
		return (NULL);
	if (!(new = mem(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
