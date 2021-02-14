/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:34:55 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 16:49:04 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	continue_pushing_2(t_data *p, t_world *w)
{
	int		i;

	i = 0;
	while (i < p->cone_num)
	{
		if (check_transform_matrix(&w->cone[i].transform,
		&w->cone[i].m.p.transform, w->cone[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cone[i]), &normal_at_cone, &intersect_cone, w);
		push_obj_conf(w, &w->cone[i].m, &w->cone[i].transform);
		i++;
	}
	i = 0;
	while (i < p->tri_num)
	{
		// w->trian[i].m = default_material();
		//w->trian[i].transform = identity_matrix();
		// printf("p1 = %f = %f = %f\n", w->trian[i].p1.c[0], w->trian[i].p1.c[1], w->trian[i].p1.c[2]);
		// printf("p2 = %f = %f = %f\n", w->trian[i].p2.c[0], w->trian[i].p2.c[1], w->trian[i].p2.c[2]);
		// printf("p3 = %f = %f = %f\n", w->trian[i].p3.c[0], w->trian[i].p3.c[1], w->trian[i].p3.c[2]);
		// printf("\n\n\n");
		if (check_transform_matrix(&w->trian[i].transform, &w->trian[i].m.p.transform, w->trian[i].m.pattern) == EXIT_FAILURE)
		{
			printf("error train\n\n\n");
			exit(err_trans_matrix());
		push_obj((void*)(&w->cub[i]), &normal_at_cube, &intersect_cube, w);
		push_obj_conf(w, &w->cub[i].m, &w->cub[i].transform);
		i++;
	}
}

void	continue_pushing(t_data *p, t_world *w)
{
	int		i;

	i = 0;
	while (i < p->cyl_num)
	{
		if (check_transform_matrix(&w->cyl[i].transform,
		&w->cyl[i].m.p.transform, w->cyl[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cyl[i]), &normal_at_cyl, &intersect_cyl, w);
		push_obj_conf(w, &w->cyl[i].m, &w->cyl[i].transform);
		i++;
	}
	i = 0;
	while (i < p->cube_num)
	{
		if (check_transform_matrix(&w->cub[i].transform,
		&w->cub[i].m.p.transform, w->cub[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cub[i]), &normal_at_cube, &intersect_cube, w);
		push_obj_conf(w, &w->cub[i].m, &w->cub[i].transform);
		i++;
	}
	continue_pushing_2(p, w);
}

void	pushing_objects(t_data *p, t_world *w)
{
	int		i;

	i = 0;
	printf("%d %d\n", p->obj_n, p->tri_num);
	while (i < p->pl_num)
	{
		if (check_transform_matrix(&w->pl[i].transform,
		&w->pl[i].m.p.transform, w->pl[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->pl[i]), &normal_at_pl, &intersect_pl, w);
		push_obj_conf(w, &w->pl[i].m, &w->pl[i].transform);
		i++;
	}
	i = 0;
	while (i < p->sp_num)
	{
		if (check_transform_matrix(&w->s[i].transform,
		&w->s[i].m.p.transform, w->s[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->s[i]), &normal_at_sp, &intersect_sp, w);
		push_obj_conf(w, &w->s[i].m, &w->s[i].transform);
		i++;
	}
	continue_pushing(p, w);
}
