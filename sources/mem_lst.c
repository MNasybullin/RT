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
	get_mem()->p = NULL;
	get_mem()->next = NULL;
	get_mem()->last = NULL;
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
	if (get_mem()->last == NULL)
		get_mem()->next = new;
	else
	{
		tmp = (t_mem*)get_mem()->last;
		tmp->next = new;
	}
	get_mem()->last = new;
}

void	del_m(void)
{
	t_mem	*tmp;
	t_mem	*curr;

	curr = (t_mem*)get_mem()->next;
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

	tmp = get_mem()->next;
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
