/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:30:35 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/22 23:30:50 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_tri(t_data *p, t_world *w)
{
	w->trian[p->tri_i].pattern = 0;
	p->tri_vect = 0;
	w->trian[p->tri_i].pattern = 0;
	w->trian[p->tri_i].is_tex = 0;
	w->trian[p->tri_i].pattern_type = 0;
	w->trian[p->tri_i].m.tex = 0;
	w->trian[p->tri_i].width = 0;
	w->trian[p->tri_i].height = 0;
	w->trian[p->tri_i].m = default_material();
}
