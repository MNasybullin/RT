/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 19:29:04 by sdiego            #+#    #+#             */
/*   Updated: 2020/10/10 18:25:52 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CH 11//
//
	//floor
	w.pl[0] = set_plane();
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.4;
	w.pl[0].transform = matrix_mult(w.pl[0].transform, rotation_y(0.31415));
	checker_pattern_shape(color(0.35, 0.35, 0.35), color(0.65,0.65,0.65), &w.pl[0].m);

	//ceiling
	w.pl[1] = set_plane();
	w.pl[1].transform = matrix_mult(w.pl[1].transform, translation(0,5,0));
	w.pl[1].m.color = color(0.8, 0.8, 0.8);
	w.pl[1].m.specular = 0;
	w.pl[1].m.ambient = 0.3;

	// west wall
	w.pl[2] = set_plane();
	w.pl[2].transform = matrix_mult(w.pl[2].transform, translation(-5, 0, 0));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_z(1.5708));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[2].m);
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, rotation_y(1.5708));
	w.pl[2].m.ambient = 0;
	w.pl[2].m.diffuse = 0.4;
	w.pl[2].m.specular = 0;
	w.pl[2].m.reflective = 0.3;

	//east wall
	w.pl[3] = set_plane();
	w.pl[3].transform = matrix_mult(w.pl[3].transform, translation(5, 0, 0));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_z(1.5708));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[3].m);
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, rotation_y(1.5708));
	w.pl[3].m.ambient = 0;
	w.pl[3].m.diffuse = 0.4;
	w.pl[3].m.specular = 0;
	w.pl[3].m.reflective = 0.3;

	//north wall
	w.pl[4] = set_plane();
	w.pl[4].transform = matrix_mult(w.pl[4].transform, translation(0, 0, 5));
	w.pl[4].transform = matrix_mult(w.pl[4].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[4].m);
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, rotation_y(1.5708));
	w.pl[4].m.ambient = 0;
	w.pl[4].m.diffuse = 0.4;
	w.pl[4].m.specular = 0;
	w.pl[4].m.reflective = 0.3;

	//south wall
	w.pl[5] = set_plane();
	w.pl[5].transform = matrix_mult(w.pl[5].transform, translation(0, 0, -5));
	w.pl[5].transform = matrix_mult(w.pl[5].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_shape(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[5].m);
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, rotation_y(1.5708));
	w.pl[5].m.ambient = 0;
	w.pl[5].m.diffuse = 0.4;
	w.pl[5].m.specular = 0;
	w.pl[5].m.reflective = 0.3;


	//background ball
	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(4.6, 0.4, 1));
	w.s[0].transform = matrix_mult(w.s[0].transform, scaling(0.4, 0.4, 0.4));
	w.s[0].m.color = (color(0.8, 0.5, 0.3));
	w.s[0].m.shininess = 50;


	//background ball
	w.s[1] = set_sphere();
	w.s[1].transform = matrix_mult(w.s[1].transform, translation(4.7, 0.3, 0.4));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(0.3,0.3,0.3));

	w.s[1].m.color = (color(0.9, 0.4, 0.5));
	w.s[1].m.shininess = 50;


	//background ball
	w.s[2] = set_sphere();
	w.s[2].transform = matrix_mult(w.s[2].transform, translation(-1, 0.5, 4.5));
	w.s[2].transform = matrix_mult(w.s[2].transform, scaling(0.5, 0.5, 0.5));
	w.s[2].m.color = (color(0.4, 0.9, 0.6));
	w.s[2].m.shininess = 50;


	//background ball
	w.s[3] = set_sphere();
	w.s[3].transform =  matrix_mult(w.s[3].transform, translation(-1.7, 0.3, 4.7));
	w.s[3].transform = matrix_mult(w.s[3].transform, scaling(0.3 ,0.3, 0.3));

	w.s[3].m.color = (color(0.4, 0.6, 0.9));
	w.s[3].m.shininess = 50;

	//foreground balls

	//red
	w.s[4] = set_sphere();
	w.s[4].transform =  matrix_mult(w.s[4].transform, translation(-0.6, 1, 0.6));
	w.s[4].m.color = (color(1, 0.3, 0.2));
	w.s[4].m.specular = 0.4;
	w.s[4].m.shininess = 5;
	//checker_pattern_shape(color(0.35, 0.35, 0.35), color(0.65,0.65,0.65), &w.s[4].m);
	//w.s[4].m.p.transform = matrix_mult(w.s[4].m.p.transform, scaling(0.25, 0.25, 0.25));

	//blue glass
	w.s[5] = set_sphere();
	w.s[5].transform =  matrix_mult(w.s[5].transform, translation(0.6, 0.7, -0.6));
	w.s[5].transform = matrix_mult(w.s[5].transform, scaling(0.7,0.7,0.7));

	w.s[5].m.color = (color(0, 0, 0.2));
	w.s[5].m.ambient = 0;
	w.s[5].m.diffuse = 0.4;
	w.s[5].m.specular = 0.9;
	w.s[5].m.shininess = 300;
	w.s[5].m.reflective = 0.9;
	w.s[5].m.transparency = 0.9;
	w.s[5].m.refractive_index = 1.5;

	//green glass
	w.s[6] = set_sphere();
	w.s[6].transform =  matrix_mult(w.s[6].transform, translation(-0.7, 0.5, -0.8));
	w.s[6].transform = matrix_mult(w.s[6].transform, scaling(0.5,0.5,0.5));

	w.s[6].m.color = (color(0, 0.2, 0));
	w.s[6].m.ambient = 0;
	w.s[6].m.diffuse = 0.4;
	w.s[6].m.specular = 0.9;
	w.s[6].m.shininess = 300;
	w.s[6].m.reflective = 0.9;
	w.s[6].m.transparency = 0.9;
	w.s[6].m.refractive_index = 1.5;

	//light
	w.light_obj = 1;
	w.light[0] = point_light(color(1, 1, 1), set_v_p(-4.9, 4.9, -1, 1));
	w.light[1] = point_light(color(1, 1, 1), set_v_p(4.9, 4.9, -1, 1));

	w.s_obj = 7;
	w.pl_obj = 6;
	w.max_obj = 13;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 1.152);
	c.transform = view_transform(set_v_p(-2.6, 1.5, -3.9, 1), set_v_p(-0.6, 1, -0.8, 1), set_v_p(0, 1, 0, 0));

















//CH 12//
//

//floor / ceiling
w.cub[0] = set_cube();
w.cub[0].transform = matrix_mult(w.cub[0].transform, scaling(20, 7, 20));
w.cub[0].transform = matrix_mult(w.cub[0].transform, translation(0, 1, 0));
checker_pattern_shape(color(0, 0, 0), color(0.25, 0.25, 0.25), &w.cub[0].m);
w.cub[0].m.p.transform = matrix_mult(w.cub[0].m.p.transform, scaling(0.07, 0.07, 0.07));
w.cub[0].m.ambient = 0.25;
w.cub[0].m.diffuse = 0.7;
w.cub[0].m.specular = 0.9;
w.cub[0].m.shininess = 300;
w.cub[0].m.reflective = 0.1;

//walls
w.cub[1] = set_cube();
w.cub[1].transform = matrix_mult(w.cub[1].transform, scaling(10, 10, 10));
checker_pattern_shape(color(0.4863, 0.3765, 0.2941), color(0.3725, 0.2902, 0.2275), &w.cub[1].m);
w.cub[1].m.p.transform = matrix_mult(w.cub[1].m.p.transform, scaling(0.05, 20, 0.05));
w.cub[1].m.ambient = 0.1;
w.cub[1].m.diffuse = 0.7;
w.cub[1].m.specular = 0.9;
w.cub[1].m.shininess = 300;
w.cub[1].m.reflective = 0.1;

//table top
w.cub[2] = set_cube();
w.cub[2].transform = matrix_mult(w.cub[2].transform, translation(0, 3.1, 0));
w.cub[2].transform = matrix_mult(w.cub[2].transform, scaling(3, 0.1, 2));
stripe_pattern_shape(color(0.5529, 0.4235, 0.3255), color(0.6588, 0.5098, 0.4000), &w.cub[2].m);
w.cub[2].m.p.transform = matrix_mult(w.cub[2].m.p.transform, scaling(0.05, 0.05, 0.05));
w.cub[2].m.p.transform = matrix_mult(w.cub[2].m.p.transform, rotation_y(0.1));
w.cub[2].m.ambient = 0.1;
w.cub[2].m.diffuse = 0.7;
w.cub[2].m.specular = 0.9;
w.cub[2].m.shininess = 300;
w.cub[2].m.reflective = 0.2;

//leg #1
w.cub[3] = set_cube();
w.cub[3].transform = matrix_mult(w.cub[3].transform, translation(2.7, 1.5, -1.7));
w.cub[3].transform = matrix_mult(w.cub[3].transform, scaling(0.1, 1.5, 0.1));
w.cub[3].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[3].m.ambient = 0.2;
w.cub[3].m.diffuse = 0.7;

//leg #2
w.cub[4] = set_cube();
w.cub[4].transform = matrix_mult(w.cub[4].transform, translation(2.7, 1.5, 1.7));
w.cub[4].transform = matrix_mult(w.cub[4].transform, scaling(0.1, 1.5, 0.1));
w.cub[4].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[4].m.ambient = 0.2;
w.cub[4].m.diffuse = 0.7;

//leg #3
w.cub[5] = set_cube();
w.cub[5].transform = matrix_mult(w.cub[5].transform, translation(-2.7, 1.5, -1.7));
w.cub[5].transform = matrix_mult(w.cub[5].transform, scaling(0.1, 1.5, 0.1));
w.cub[5].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[5].m.ambient = 0.2;
w.cub[5].m.diffuse = 0.7;

//leg #4
w.cub[6] = set_cube();
w.cub[6].transform = matrix_mult(w.cub[6].transform, translation(-2.7, 1.5, 1.7));
w.cub[6].transform = matrix_mult(w.cub[6].transform, scaling(0.1, 1.5, 0.1));
w.cub[6].m.color = color(0.5529, 0.4235, 0.3255);
w.cub[6].m.ambient = 0.2;
w.cub[6].m.diffuse = 0.7;

//glass cube
w.cub[7] = set_cube();
w.cub[7].transform = matrix_mult(w.cub[7].transform, translation(0, 3.45001, 0));
w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_y(0.2));
w.cub[7].transform = matrix_mult(w.cub[7].transform, scaling(0.25, 0.25, 0.25));
w.cub[7].m.color = color(1, 1, 0.8);
w.cub[7].m.ambient = 0;
w.cub[7].m.diffuse = 0.3;
w.cub[7].m.specular = 0.9;
w.cub[7].m.shininess = 300;
w.cub[7].m.reflective = 0.7;
w.cub[7].m.transparency = 0.7;
w.cub[7].m.refractive_index = 1.5;
w.cub[7].m.shadow = 0;

//little cube #1
w.cub[8] = set_cube();
w.cub[8].transform = matrix_mult(w.cub[8].transform, translation(1, 3.35, -0.9));
w.cub[8].transform = matrix_mult(w.cub[8].transform, scaling(0.15, 0.15, 0.15));
w.cub[8].transform = matrix_mult(w.cub[8].transform, rotation_y(-0.4));
w.cub[8].m.color = color(1, 0.5, 0.5);
w.cub[8].m.reflective = 0.6;
w.cub[8].m.diffuse = 0.4;

//little cube #2
w.cub[9] = set_cube();
w.cub[9].transform = matrix_mult(w.cub[9].transform, translation(-1.5, 3.27, 0.3));
w.cub[9].transform = matrix_mult(w.cub[9].transform, rotation_y(0.4));
w.cub[9].transform = matrix_mult(w.cub[9].transform, scaling(0.15, 0.07, 0.15));
w.cub[9].m.color = color(1, 1, 0.5);

//little cube #3
w.cub[10] = set_cube();
w.cub[10].transform = matrix_mult(w.cub[10].transform, translation(0, 3.25, 1));
w.cub[10].transform = matrix_mult(w.cub[10].transform, rotation_y(0.4));
w.cub[10].transform = matrix_mult(w.cub[10].transform, scaling(0.2, 0.05, 0.05));
w.cub[10].m.color = color(0.5, 1, 0.5);

//little cube #4
w.cub[11] = set_cube();
w.cub[11].transform = matrix_mult(w.cub[11].transform, translation(-0.6, 3.4, -1));
w.cub[11].transform = matrix_mult(w.cub[11].transform, rotation_y(0.8));
w.cub[11].transform = matrix_mult(w.cub[11].transform, scaling(0.05, 0.2, 0.05));
w.cub[11].m.color = color(0.5, 0.5, 1);

//little cube #5
w.cub[12] = set_cube();
w.cub[12].transform = matrix_mult(w.cub[12].transform, translation(2, 3.4, 1));
w.cub[12].transform = matrix_mult(w.cub[12].transform, rotation_y(0.8));
w.cub[12].transform = matrix_mult(w.cub[12].transform, scaling(0.05, 0.2, 0.05));
w.cub[12].m.color = color(0.5, 1, 1);

//frame #1
w.cub[13] = set_cube();
w.cub[13].transform = matrix_mult(w.cub[13].transform, translation(-10, 4, 1));
w.cub[13].transform = matrix_mult(w.cub[13].transform, scaling(0.05, 1, 1));
w.cub[13].m.color = color(0.7098, 0.2471, 0.2196);
w.cub[13].m.diffuse = 0.6;

//frame #2
w.cub[14] = set_cube();
w.cub[14].transform = matrix_mult(w.cub[14].transform, translation(-10, 3.4, 2.7));
w.cub[14].transform = matrix_mult(w.cub[14].transform, scaling(0.05, 0.4, 0.4));
w.cub[14].m.color = color(0.2667, 0.2706, 0.6902);
w.cub[14].m.diffuse = 0.6;

//frame #3
w.cub[15] = set_cube();
w.cub[15].transform = matrix_mult(w.cub[15].transform, translation(-10, 4.6, 2.7));
w.cub[15].transform = matrix_mult(w.cub[15].transform, scaling(0.05, 0.4, 0.4));
w.cub[15].m.color = color(0.3098, 0.5961, 0.3098);
w.cub[15].m.diffuse = 0.6;

//mirror frame
w.cub[16] = set_cube();
w.cub[16].transform = matrix_mult(w.cub[16].transform, translation(-2, 3.5, 9.95));
w.cub[16].transform = matrix_mult(w.cub[16].transform, scaling(5, 1.5, 0.05));
w.cub[16].m.color = color(0.3882, 0.2627, 0.1882);
w.cub[16].m.diffuse = 0.7;

//mirror
w.cub[17] = set_cube();
w.cub[17].transform = matrix_mult(w.cub[17].transform, translation(-2, 3.5, 9.95));
w.cub[17].transform = matrix_mult(w.cub[17].transform, scaling(4.8, 1.4, 0.06));
w.cub[17].m.color = color(0, 0, 0);
w.cub[17].m.diffuse = 0;
w.cub[17].m.ambient = 0;
w.cub[17].m.specular = 1;
w.cub[17].m.shininess = 300;
w.cub[17].m.reflective = 1;

//light
w.light_obj = 1;
w.light[0] = point_light(color(1, 1, 0.9), set_v_p(0, 6.9, -5, 1));
w.cub_obj = 18;
w.max_obj = 18;
w.ar_count = 0;
int i = 0;
while (i < w.max_obj)
{
	if (check_transform_matrix(w.cub[i].transform, w.cub[i].m.p.transform, w.cub[i].m.pattern) == EXIT_FAILURE)
		exit(-1); // нужно сделать правильный выход из программы
	push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
	i++;
}

t_camera c = camera(WIN_W, WIN_H, 0.785);
c.transform = view_transform(set_v_p(8, 6, -8, 1), set_v_p(0, 3, 0, 1), set_v_p(0, 1, 0, 0));





// SOFT SHADOW
//
	//floor
	w.pl[0] = set_plane();
	w.pl[0].m.color = color(1, 1, 1);
	w.pl[0].m.specular = 0;
	w.pl[0].m.diffuse = 0.67;
	w.pl[0].m.ambient = 0.025;

	//background ball
	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(0.5, 0.5, 0));
	w.s[0].transform = matrix_mult(w.s[0].transform, scaling(0.5, 0.5, 0.5));
	w.s[0].m.color = (color(1, 0, 0));
	w.s[0].m.ambient = 0.1;
	w.s[0].m.specular = 0;
	w.s[0].m.diffuse = 0.6;
	w.s[0].m.reflective = 0.3;


	//background ball
	w.s[1] = set_sphere();
	w.s[1].transform = matrix_mult(w.s[1].transform, translation(-0.25, 0.33, 0));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(0.33,0.33,0.33));
	w.s[1].m.color = (color(0.5, 0.5, 1));
	w.s[1].m.ambient = 0.1;
	w.s[1].m.specular = 0;
	w.s[1].m.diffuse = 0.6;
	w.s[1].m.reflective = 0.3;

	w.cub[0] = set_cube();
	w.cub[0].transform = matrix_mult(w.cub[0].transform, translation(0, 3, 4));
	w.cub[0].transform = matrix_mult(w.cub[0].transform, scaling(1, 1, 0.01));
	w.cub[0].m.color = color(1.5, 1.5, 1.5);
	w.cub[0].m.specular = 0;
	w.cub[0].m.diffuse = 0;
	w.cub[0].m.ambient = 1;
	w.cub[0].m.shadow = 0;


	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-1, 2, 4, 1);
	t_vec v1 = set_v_p(2, 0, 0, 0);
	t_vec v2 = set_v_p(0, 2, 0, 0);
	w.light[0] = area_light(corner, v1, 10, v2, 10, color(1.5, 1.5, 1.5));

	w.s_obj = 2;
	w.pl_obj = 1;
	w.cub_obj = 1;
	w.max_obj = 4;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	i = 0;
	while (i < w.cub_obj)
	{
		if (check_transform_matrix(w.cub[i].transform, w.cub[i].m.p.transform, w.cub[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.7854);
	c.transform = view_transform(set_v_p(-3, 1, 2.5, 1), set_v_p(0, 0.5, 0, 1), set_v_p(0, 1, 0, 0));









// Texture mapping
// sphere checkers pattern
	w.s[0] = set_sphere();
	w.s[0].m.pattern = 1;
	w.s[0].m.p = uv_checkers(20, 10, color(0, 0.5, 0), color(1, 1, 1));
	w.s[0].m.pattern_at = &pattern_at;
	w.s[0].m.p.transform = identity_matrix();
	w.s[0].m.texturemap = texture_map(w.s[0].m.p, &spherical_map);
	w.s[0].m.ambient = 0.1;
	w.s[0].m.specular = 0.4;
	w.s[0].m.diffuse = 0.6;
	w.s[0].m.shininess = 10;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-10, 10, -10, 1);
	t_vec v1 = set_v_p(1, 0, 0, 0);
	t_vec v2 = set_v_p(0, 1, 0, 0);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.s_obj = 1;
	w.max_obj = 4;
	w.ar_count = 0;

	int i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.5);
	c.transform = view_transform(set_v_p(0, 0, -5, 1), set_v_p(0, 0, 0, 1), set_v_p(0, 1, 0, 0));




// Texture mapping
// planar checkers pattern
	w.pl[0] = set_plane();
	w.pl[0].m.pattern = 1;
	w.pl[0].m.p = uv_checkers(2, 2, color(0, 0.5, 0), color(1, 1, 1));
	w.pl[0].m.pattern_at = &pattern_at;
	w.pl[0].m.p.transform = identity_matrix();
	w.pl[0].m.texturemap = texture_map(w.pl[0].m.p, &planar_map);
	w.pl[0].m.ambient = 0.1;
	w.pl[0].m.specular = 0;
	w.pl[0].m.diffuse = 0.9;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-10, 10, -10, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.pl_obj = 1;
	w.max_obj = 4;
	w.ar_count = 0;

	int i = 0;
	while (i < w.pl_obj)
	{
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.5);
	c.transform = view_transform(set_v_p(1, 2, -5, 1), set_v_p(0, 0, 0, 1), set_v_p(0, 1, 0, 0));




// Texture mapping
// cylindrical checkers pattern
	w.cyl[0] = set_cylinder();
	w.cyl[0].min = 0;
	w.cyl[0].max = 1;
	w.cyl[0].closed = 1;
	w.cyl[0].m.pattern = 1;
	w.cyl[0].transform = matrix_mult(w.cyl[0].transform, scaling(1, 3.1415, 1));
	w.cyl[0].transform = matrix_mult(w.cyl[0].transform, translation(0, -0.5, 0));
	w.cyl[0].m.p = uv_checkers(16, 8, color(0, 0.5, 0), color(1, 1, 1));
	w.cyl[0].m.pattern_at = &pattern_at;
	w.cyl[0].m.p.transform = identity_matrix();
	w.cyl[0].m.texturemap = texture_map(w.cyl[0].m.p, &cylindrical_map);
	w.cyl[0].m.ambient = 0.1;
	w.cyl[0].m.specular = 0.6;
	w.cyl[0].m.diffuse = 0.8;
	w.cyl[0].m.shininess = 15;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-10, 10, -10, 1);
	t_vec v1 = set_v_p(1, 0, 0, 0);
	t_vec v2 = set_v_p(0, 1, 0, 0);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.cyl_obj = 1;
	w.max_obj = 4;
	w.ar_count = 0;

	int i = 0;
	while (i < w.cyl_obj)
	{
		if (check_transform_matrix(w.cyl[i].transform, w.cyl[i].m.p.transform, w.cyl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cyl[i]), &normal_at_cyl, &intersect_cyl, &w, &w.cyl[i].m, &w.cyl[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.5);
	c.transform = view_transform(set_v_p(0, 0, -10, 1), set_v_p(0, 0, 0, 1), set_v_p(0, 1, 0, 0));


















	// Texture mapping
// cube
	t_color red = color(1, 0, 0);
	t_color yellow = color(1, 1, 0);
	t_color brown = color(1, 0.5, 0);
	t_color green = color(0, 1, 0);
	t_color cyan = color(0, 1, 1);
	t_color blue = color(0, 0, 1);
	t_color purple = color(1, 0, 1);
	t_color white = color(1, 1, 1);
	t_pattern pattern;
	pattern = uv_align_check(yellow, cyan, red, blue, brown, 1);
	pattern = uv_align_check(cyan, red, yellow, brown, green, 4);
    pattern = uv_align_check(red, yellow, purple, green, white, 0);
    pattern = uv_align_check(green, purple, cyan, white, blue, 5);
    pattern = uv_align_check(brown, cyan, purple, red, yellow, 2);
    pattern = uv_align_check(purple, brown, green, blue, white, 3);

	w.cub[0] = set_cube();
	w.cub[0].transform = matrix_mult(w.cub[0].transform, translation(-6, 2, 0));
	w.cub[0].transform = matrix_mult(w.cub[0].transform, rotation_x(0.7854));
	w.cub[0].transform = matrix_mult(w.cub[0].transform, rotation_y(0.7854));
	w.cub[0].m.pattern = 1;
	w.cub[0].m.p = pattern;
	w.cub[0].m.p.transform = identity_matrix();
	w.cub[0].m.pattern_at = &pattern_at_cube;
	w.cub[0].m.ambient = 0.2;
	w.cub[0].m.specular = 0;
	w.cub[0].m.diffuse = 0.8;

	w.cub[1] = set_cube();
	w.cub[1].transform = matrix_mult(w.cub[1].transform, translation(-2, 2, 0));
	w.cub[1].transform = matrix_mult(w.cub[1].transform, rotation_x(0.7854));
	w.cub[1].transform = matrix_mult(w.cub[1].transform, rotation_y(2.3562));
	w.cub[1].m.pattern = 1;
	w.cub[1].m.p = pattern;
	w.cub[1].m.p.transform = identity_matrix();
	w.cub[1].m.pattern_at = &pattern_at_cube;
	w.cub[1].m.ambient = 0.2;
	w.cub[1].m.specular = 0;
	w.cub[1].m.diffuse = 0.8;

	w.cub[2] = set_cube();
	w.cub[2].transform = matrix_mult(w.cub[2].transform, translation(2, 2, 0));
	w.cub[2].transform = matrix_mult(w.cub[2].transform, rotation_x(0.7854));
	w.cub[2].transform = matrix_mult(w.cub[2].transform, rotation_y(3.927));
	w.cub[2].m.pattern = 1;
	w.cub[2].m.p = pattern;
	w.cub[2].m.p.transform = identity_matrix();
	w.cub[2].m.pattern_at = &pattern_at_cube;
	w.cub[2].m.ambient = 0.2;
	w.cub[2].m.specular = 0;
	w.cub[2].m.diffuse = 0.8;

	w.cub[3] = set_cube();
	w.cub[3].transform = matrix_mult(w.cub[3].transform, translation(6, 2, 0));
	w.cub[3].transform = matrix_mult(w.cub[3].transform, rotation_x(0.7854));
	w.cub[3].transform = matrix_mult(w.cub[3].transform, rotation_y(5.4978));
	w.cub[3].m.pattern = 1;
	w.cub[3].m.p = pattern;
	w.cub[3].m.p.transform = identity_matrix();
	w.cub[3].m.pattern_at = &pattern_at_cube;
	w.cub[3].m.ambient = 0.2;
	w.cub[3].m.specular = 0;
	w.cub[3].m.diffuse = 0.8;

	w.cub[4] = set_cube();
	w.cub[4].transform = matrix_mult(w.cub[4].transform, translation(-6, -2, 0));
	w.cub[4].transform = matrix_mult(w.cub[4].transform, rotation_x(-0.7854));
	w.cub[4].transform = matrix_mult(w.cub[4].transform, rotation_y(0.7854));
	w.cub[4].m.pattern = 1;
	w.cub[4].m.p = pattern;
	w.cub[4].m.p.transform = identity_matrix();
	w.cub[4].m.pattern_at = &pattern_at_cube;
	w.cub[4].m.ambient = 0.2;
	w.cub[4].m.specular = 0;
	w.cub[4].m.diffuse = 0.8;

	w.cub[5] = set_cube();
	w.cub[5].transform = matrix_mult(w.cub[5].transform, translation(-2, -2, 0));
	w.cub[5].transform = matrix_mult(w.cub[5].transform, rotation_x(-0.7854));
	w.cub[5].transform = matrix_mult(w.cub[5].transform, rotation_y(2.3562));
	w.cub[5].m.pattern = 1;
	w.cub[5].m.p = pattern;
	w.cub[5].m.p.transform = identity_matrix();
	w.cub[5].m.pattern_at = &pattern_at_cube;
	w.cub[5].m.ambient = 0.2;
	w.cub[5].m.specular = 0;
	w.cub[5].m.diffuse = 0.8;

	w.cub[6] = set_cube();
	w.cub[6].transform = matrix_mult(w.cub[6].transform, translation(2, -2, 0));
	w.cub[6].transform = matrix_mult(w.cub[6].transform, rotation_x(-0.7854));
	w.cub[6].transform = matrix_mult(w.cub[6].transform, rotation_y(3.927));
	w.cub[6].m.pattern = 1;
	w.cub[6].m.p = pattern;
	w.cub[6].m.p.transform = identity_matrix();
	w.cub[6].m.pattern_at = &pattern_at_cube;
	w.cub[6].m.ambient = 0.2;
	w.cub[6].m.specular = 0;
	w.cub[6].m.diffuse = 0.8;

	w.cub[7] = set_cube();
	w.cub[7].transform = matrix_mult(w.cub[7].transform, translation(6, -2, 0));
	w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_x(-0.7854));
	w.cub[7].transform = matrix_mult(w.cub[7].transform, rotation_y(5.4978));
	w.cub[7].m.pattern = 1;
	w.cub[7].m.p = pattern;
	w.cub[7].m.p.transform = identity_matrix();
	w.cub[7].m.pattern_at = &pattern_at_cube;
	w.cub[7].m.ambient = 0.2;
	w.cub[7].m.specular = 0;
	w.cub[7].m.diffuse = 0.8;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(0, 0, -20, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.cub_obj = 8;
	w.max_obj = 8;
	w.ar_count = 0;

	int i = 0;
	while (i < w.cub_obj)
	{
		if (check_transform_matrix(w.cub[i].transform, w.cub[i].m.p.transform, w.cub[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.8); // 800 x 400
	c.transform = view_transform(set_v_p(0, 0, -20, 1), set_v_p(0, 0, 0, 1), set_v_p(0, 1, 0, 0));


















// cub text
	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(0, 0, 5));
	w.s[0].transform = matrix_mult(w.s[0].transform, scaling(0.75, 0.75, 0.75));
	w.s[0].m.ambient = 0;
	w.s[0].m.specular = 0.6;
	w.s[0].m.diffuse = 0.4;
	w.s[0].m.shininess = 20;
	w.s[0].m.reflective = 0.6;

	w.cub[0] = set_cube();
	w.cub[0].transform = matrix_mult(w.cub[0].transform, scaling(1000, 1000, 1000));
	w.cub[0].m.ambient = 1;
	w.cub[0].m.specular = 0;
	w.cub[0].m.diffuse = 0;
	w.cub[0].m.tex = 1;
	w.cub[0].m.pattern = 1;
	w.cub[0].m.pattern_at = &pattern_at_cube_texture;
	w.cub[0].m.p.transform = identity_matrix();
	w.cub[0].m.p.cube_texture[0] = SDL_LoadBMP("textures/posx.bmp"); //right | posx
	w.cub[0].m.p.cube_texture[1] = SDL_LoadBMP("textures/negx.bmp"); //left | negx
	w.cub[0].m.p.cube_texture[2] = SDL_LoadBMP("textures/posy.bmp"); //up | posy
	w.cub[0].m.p.cube_texture[3] = SDL_LoadBMP("textures/negy.bmp"); //down | negy
	w.cub[0].m.p.cube_texture[4] = SDL_LoadBMP("textures/posz.bmp"); //front | posz
	w.cub[0].m.p.cube_texture[5] = SDL_LoadBMP("textures/negz.bmp"); //back | negz


	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(0, 100, 0, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.s_obj = 1;
	w.cub_obj = 1;
	w.max_obj = 2;
	w.ar_count = 0;

	int i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	i = 0;
	while (i < w.cub_obj)
	{
		if (check_transform_matrix(w.cub[i].transform, w.cub[i].m.p.transform, w.cub[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cub[i]), &normal_at_cube, &intersect_cube, &w, &w.cub[i].m, &w.cub[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 1.2); // 800x800
	c.transform = view_transform(set_v_p(0, 0, 0, 1), set_v_p(0, 0, 5, 1), set_v_p(0, 1, 0, 0));





























// EARTH

	w.pl[0] = set_plane();
	w.pl[0].m.color = color(1, 1, 1);
	w.pl[0].m.ambient = 0;
	w.pl[0].m.specular = 0;
	w.pl[0].m.diffuse = 0.1;
	w.pl[0].m.reflective = 0.4;

	w.cyl[0] = set_cylinder();
	w.cyl[0].min = 0;
	w.cyl[0].max = 0.1;
	w.cyl[0].closed = 1;
	w.cyl[0].m.color = color(1, 1, 1);
	w.cyl[0].m.ambient = 0;
	w.cyl[0].m.specular = 0;
	w.cyl[0].m.diffuse = 0.2;
	w.cyl[0].m.reflective = 0.1;

	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(0, 1.1, 0));
	w.s[0].transform = matrix_mult(w.s[0].transform, rotation_y(1.9));

	w.s[0].m.pattern = 1;
	w.s[0].m.p = uv_checkers(20, 10, color(0, 0.5, 0), color(1, 1, 1));
	w.s[0].m.pattern_at = &pattern_at;
	w.s[0].m.p.transform = identity_matrix();
	w.s[0].m.texture = SDL_LoadBMP("textures/earthmap1k.bmp");
	w.s[0].m.tex = 1;
	w.s[0].m.texturemap = texture_map(w.s[0].m.p, &spherical_map);
	w.s[0].m.ambient = 0.1;
	w.s[0].m.specular = 0.1;
	w.s[0].m.diffuse = 0.9;
	w.s[0].m.shininess = 10;

	//light
	w.light_obj = 1;
	t_vec corner = set_v_p(-100, 100, -100, 1);
	w.light[0] = point_light(color(1, 1, 1), corner);

	w.s_obj = 1;
	w.pl_obj = 1;
	w.cyl_obj = 1;
	w.ar_count = 0;

	int i = 0;
	while (i < w.s_obj)
	{
		if (check_transform_matrix(w.s[i].transform, w.s[i].m.p.transform, w.s[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &w, &w.s[i].m, &w.s[i].transform);
		i++;
	}

	i = 0;
	while (i < w.pl_obj)
	{
		if (check_transform_matrix(w.pl[i].transform, w.pl[i].m.p.transform, w.pl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &w, &w.pl[i].m, &w.pl[i].transform);
		i++;
	}

	i = 0;
	while (i < w.cyl_obj)
	{
		if (check_transform_matrix(w.cyl[i].transform, w.cyl[i].m.p.transform, w.cyl[i].m.pattern) == EXIT_FAILURE)
			exit(-1); // нужно сделать правильный выход из программы
		push_obj((void*)(&w.cyl[i]), &normal_at_cyl, &intersect_cyl, &w, &w.cyl[i].m, &w.cyl[i].transform);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 0.8);
	c.transform = view_transform(set_v_p(1, 2, -10, 1), set_v_p(0, 1.1, 0, 1), set_v_p(0, 1, 0, 0));
