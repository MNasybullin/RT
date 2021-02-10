/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 09:09:41 by aannara           #+#    #+#             */
/*   Updated: 2020/12/14 16:41:10 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_m(void)
{
	g_m.p = NULL;
	g_m.next = NULL;
	g_m.last = NULL;
}

void	new_m(void *pointer)
{
	t_mem	*new;
	t_mem	*tmp;

	if (!(new = (t_mem*)malloc(sizeof(t_mem))))
		exit(EXIT_FAILURE);
	new->p = pointer;
	new->next = NULL;
	new->last = new;
	if (g_m.last == NULL)
		g_m.next = new;
	else
	{
		tmp = (t_mem*)g_m.last;
		tmp->next = new;
	}
	g_m.last = new;
}

void	del_m(void)
{
	t_mem	*tmp;
	t_mem	*curr;

	curr = (t_mem*)g_m.next;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}

void	del_memory(void)
{
	t_mem	*tmp;

	tmp = g_m.next;
	while (tmp != NULL)
	{
		free(tmp->p);
		tmp = tmp->next;
	}
	del_m();
}

void	*mem(size_t size)
{
	void	*p;

	if (!(p = malloc(size)))
		exit(EXIT_FAILURE);
	new_m(p);
	return (p);
}
