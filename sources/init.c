/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:35:51 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 16:42:37 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_parse(t_data *p, t_world *w)
{
	p->pl_num = 0;
	p->sp_num = 0;
	p->cone_num = 0;
	p->cyl_num = 0;
	p->cube_num = 0;
	p->tri_num = 0;
	p->lights_num = 0;
	p->pl_i = 0;
	p->sp_i = 0;
	p->cone_i = 0;
	p->cyl_i = 0;
	p->cube_i = 0;
	p->tri_i = 0;
	p->light_i = 0;
	p->cam_num = 0;
	w->pl_obj += 0;
	p->is_obj_file = 0;
}

void	init_cyl(t_data *p, t_world *w)
{
	w->cyl[p->cyl_i] = set_cylinder();
	w->cyl[p->cyl_i].pattern = 0;
	w->cyl[p->cyl_i].is_tex = 0;
	w->cyl[p->cyl_i].pattern_type = 0;
	w->cyl[p->cyl_i].m.tex = 0;
	w->cyl[p->cyl_i].width = 0;
	w->cyl[p->cyl_i].height = 0;
	w->cyl[p->cyl_i].check.height = 0;
	w->cyl[p->cyl_i].check.width = 0;
}
