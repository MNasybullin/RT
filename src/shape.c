/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2020/12/01 16:04:21 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
void    push_pat(t_color (*pattern_at)(t_pattern, void *, t_vec), t_world *w)
{
    w->pl[0].m.pattern_at = pattern_at;
}
*/

void    push_obj(void *obj, int (*loc_norm)(void *, t_vec, t_vec*),
void (*loc_intersect)(void *, t_ray, t_x_t*, int), t_world *w, t_material *m, t_matrix *transform)
{
    w->obj_ar[w->ar_count].obj = obj;
    w->obj_ar[w->ar_count].loc_norm = loc_norm;
    w->obj_ar[w->ar_count].loc_intersect = loc_intersect;
    w->obj_ar[w->ar_count].m = m;
    w->obj_ar[w->ar_count].transform = transform;
    w->ar_count++;
}











