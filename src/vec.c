/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:13:49 by aannara           #+#    #+#             */
/*   Updated: 2020/12/12 14:59:55 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
** d = 0.0 - vector
** d = 1.0 - point
*/

t_vec	set_v_p(double a, double b, double c, double d)
{
	t_vec	t;

	t.c[0] = a;
	t.c[1] = b;
	t.c[2] = c;
	t.c[3] = d;
	return (t);
}

t_t_o	*alloc_tto(int size)
{
	t_t_o	*i;

	if ((i = (t_t_o *)malloc(sizeof(t_t_o) * (size * 4))) == NULL)
	{
		write(1, "malloc alloc_tto error\n", 23);
		exit(EXIT_FAILURE);
	}
	return (i);
}

int		*alloc_int(int size)
{
	int	*i;

	if ((i = (int *)malloc(sizeof(int) * (size * 4))) == NULL)
	{
		write(1, "malloc alloc_int error\n", 23);
		exit(EXIT_FAILURE);
	}
	return (i);
}

void	free_tto(t_t_o *tto)
{
	free(tto);
	tto = NULL;
}

void	free_int(int *i)
{
	free(i);
	i = NULL;
}
