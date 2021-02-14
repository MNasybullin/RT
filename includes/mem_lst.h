/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 09:05:51 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 13:52:31 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_LST_H
# define MEM_LST_H

# include "rt.h"

typedef struct	s_mem
{
	void		*p;
	void		*next;
	void		*last;
}				t_mem;

t_mem			*get_mem();

void			set_m(void);
void			new_m(void *pointer);
void			del_m(void);
void			del_memory(void);
void			*mem(size_t size);

#endif
