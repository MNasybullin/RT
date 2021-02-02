/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:35:51 by mgalt             #+#    #+#             */
/*   Updated: 2020/12/03 21:34:52 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
}
