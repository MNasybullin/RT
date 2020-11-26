/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 20:14:25 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 18:42:18 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"
#include "libft.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	//ft_putendl("\n\nin len tab\n\n");
	while (tab[i] != 0)
		i++;
	//ft_putendl("\n\nend of len tab\n\n");
	return (i);
}

int		check_make_obj(char **tab)
{
	//ft_putendl("\n\nstart of check make obj\n\n");
	if (len_tab(tab) >= 2 && !(ft_strequ(tab[0], "-")) &&!(ft_strequ(tab[1], "object:")) &&
		!(ft_strequ(tab[0], "lights:")) && !(ft_strequ(tab[1], "light:")) &&
		!(ft_strequ(tab[0], "cameras:")) && !(ft_strequ(tab[1], "camera:")))
		return (1);
	return (0);
}

int		check_format(char *file)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	i = len - 4;
	if (file[i] == '.' && file[i + 1] == 'y' &&
	file[i + 2] == 'm' && file[i + 3] == 'l')
		return (1);
	else
		return(0);
}

void	count_objects(t_data *p, char *file, char *line)
{
	char	**tab;
	int		len = 0;

	//printf("line: %s\n", p->line);
	//ft_putendl("count_objects");
	get_next_line(p->fd, &line);
	//printf("line: %s\n", p->line);
	tab = NULL;
	while ((get_next_line(p->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		len = len_tab(tab);
		if (len == 2)
		{
			if (!(ft_strcmp(tab[0], "type:")))
			{
				if (!(ft_strcmp(tab[1], "plane")))
					p->pl_num++;
				if (!(ft_strcmp(tab[1], "sphere")))
					p->sp_num++;
				if (!(ft_strcmp(tab[1], "cone")))
					p->cone_num++;
				if (!(ft_strcmp(tab[1], "cylinder")))
					p->cyl_num++;
				if (!(ft_strcmp(tab[1], "cube")))
					p->cube_num++;
				if (!(ft_strcmp(tab[1], "triangle")))
					p->tri_num++;
			}
			free_tab(tab);
			tab = NULL;
		}
	}
	p->obj_n = p->pl_num + p->sp_num + p->cone_num + p->cyl_num + p->cube_num + p->tri_num;
	printf("\n%d %d %d %d %d %d\n\n", p->pl_num, p->sp_num, p->cone_num, p->cyl_num, p->cube_num, p->tri_num);
	close(p->fd);
}

void	alloc_obj_memory(t_data *p, t_world *w)
{
	//ft_putendl("alloc obj memory");
	if (p->pl_num)
		w->pl = (t_plane*)malloc(sizeof(t_plane) * p->pl_num);
	if (p->sp_num)
		w->s = (t_sp*)malloc(sizeof(t_sp) * p->sp_num);
	if (p->cone_num)
		w->cone = (t_cone*)malloc(sizeof(t_cone) * p->cone_num);
	if (p->cyl_num)
		w->cyl = (t_cyl*)malloc(sizeof(t_cyl) * p->cyl_num);
	if (p->cube_num)
		w->cub = (t_cube*)malloc(sizeof(t_cube) * p->cube_num);
	if (p->tri_num)
		w->trian = (t_trian*)malloc(sizeof(t_trian) * p->tri_num);	
	//ft_putendl("after alloc obj memory");	
}

void	print_parameters(t_world *w, t_data *p)
{
	ft_putendl("\nprint parameters\n");
	printf("plane1:\n---\nspec: %.1f\nreflection: %.1f\n\n", w->pl[0].m.specular, w->pl[0].m.reflective);
	printf("plane2:\n---\nspec: %.1f\nambient: %.1f\n\n", w->pl[1].m.specular, w->pl[1].m.ambient);
	printf("plane3:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[2].m.specular, w->pl[2].m.reflective, w->pl[2].m.diffuse, w->pl[2].m.ambient);
	printf("plane4:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[3].m.specular, w->pl[3].m.reflective, w->pl[3].m.diffuse, w->pl[3].m.ambient);
	printf("plane5:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[4].m.specular, w->pl[4].m.reflective, w->pl[4].m.diffuse, w->pl[4].m.ambient);
	printf("plane6:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\n\n", w->pl[5].m.specular, w->pl[5].m.reflective, w->pl[5].m.diffuse, w->pl[5].m.ambient);
	
	printf("sphere1:\n---\nshine: %.1f\n\n", w->s[0].m.shininess);
	printf("sphere2:\n---\nshine: %.1f\n\n", w->s[1].m.shininess);
	printf("sphere3:\n---\nshine: %.1f\n\n", w->s[2].m.shininess);
	printf("sphere4:\n---\nshine: %.1f\n\n", w->s[3].m.shininess);
	printf("sphere5:\n---\nspec: %.1f\nshine: %.1f\n\n", w->s[4].m.specular, w->s[4].m.shininess);
	printf("sphere6:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\nshine: %.1f\ntransparency: %.1f\nrefract: %.1f\n\n", w->s[5].m.specular, w->s[5].m.reflective, w->s[5].m.diffuse, w->s[5].m.ambient, w->s[5].m.shininess, w->s[5].m.transparency,w->s[5].m.refractive_index);
	printf("sphere7:\n---\nspec: %.1f\nreflection: %.1f\ndiffuse: %.1f\nambient: %.1f\nshine: %.1f\ntransparency: %.1f\nrefract: %.1f\n\n", w->s[6].m.specular, w->s[6].m.reflective, w->s[6].m.diffuse, w->s[6].m.ambient, w->s[6].m.shininess, w->s[6].m.transparency,w->s[6].m.refractive_index);
}

char	**check_type(t_data *p, t_world *w, char **tab)
{
	ft_putendl("\n\ncheck_type\n\n");

	if (!(ft_strcmp(tab[1], "plane")))
		p->tab = make_plane(p, w, tab);
	if (!(ft_strcmp(tab[1], "sphere")))
		p->tab = make_sphere(p, w, tab);
	if (!(ft_strcmp(tab[1], "cone")))
		p->tab = make_cone(p, w, tab);
	if (!(ft_strcmp(tab[1], "cylinder")))
		p->tab = make_cyl(p, w, tab);
	if (!(ft_strcmp(tab[1], "cube")))
		make_cube(p, w, tab);
	if (!(ft_strcmp(tab[1], "triangle")))
		make_tri(p, w, tab);
	return (p->tab);
}

void	pushing_objects(t_data *p, t_world *w)
{
	int		i;

	i = 0;
	while (i < p->pl_num)
	{
		if (check_transform_matrix(w->pl[i].transform, w->pl[i].m.p.transform, w->pl[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->pl[i]), &normal_at_pl, &intersect_pl, &w, &w->pl[i].m, &w->pl[i].transform);
		i++;
	}
	i = 0;
	while (i < p->sp_num)
	{
		if (check_transform_matrix(w->s[i].transform, w->s[i].m.p.transform, w->s[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->s[i]), &normal_at_sp, &intersect_sp, &w, &w->s[i].m, &w->s[i].transform);
		i++;
	}
	i = 0;
	while (i < p->cone_num)
	{
		if (check_transform_matrix(w->cone[i].transform, w->cone[i].m.p.transform, w->cone[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cone[i]), &normal_at_cone, &intersect_cone, &w, &w->cone[i].m, &w->cone[i].transform);
		i++;
	}
	i = 0;
	while (i < p->cyl_num)
	{
		if (check_transform_matrix(w->cyl[i].transform, w->cyl[i].m.p.transform, w->cyl[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cyl[i]), &normal_at_cyl, &intersect_cyl, &w, &w->cyl[i].m, &w->cyl[i].transform);
		i++;
	}
	i = 0;
	while (i < p->cube_num)
	{
		if (check_transform_matrix(w->cub[i].transform, w->cub[i].m.p.transform, w->cub[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->cub[i]), &normal_at_cube, &intersect_cube, &w, &w->cub[i].m, &w->cub[i].transform);
		i++;
	}
	i = 0;
	while (i < p->tri_num)
	{
		if (check_transform_matrix(w->trian[i].transform, w->trian[i].m.p.transform, w->trian[i].m.pattern) == EXIT_FAILURE)
			exit(err_trans_matrix());
		push_obj((void*)(&w->trian[i]), &normal_at_trian, &intersect_trian, &w, &w->trian[i].m, &w->trian[i].transform);
		i++;
	}
}

int		valid_len(char ***tab, int len, t_data *p)
{
	//ft_putendl("in valid len");
	//printf("Len tab is %d\n\n", len_tab(*tab));
	if ((len_tab(*tab)) == len)
			return (1);
	while ((len_tab(*tab)) != len)
	{
		free_tab(*tab);
		get_next_line(p->fd, &p->line);
		//if (len_tab(*tab) == len)
		//	return(1);
		//if (get_next_line(p->fd, &p->line) == -1)
		//	return(0);
		*tab = ft_strsplit(p->line, ' ');
		//printf("tab len: %d\n", len_tab(*tab));
		if ((len_tab(*tab)) == len)
			return (1);
	}
	return (0);
}

void	skip_empty_lines(t_data *p)
{
	while ((get_next_line(p->fd, &p->line)) && !(ft_strcmp(p->line, "\n")))
		get_next_line(p->fd, &p->line);
}

void	start_count_obj(t_data *p, char *file, t_world *w)
{
	char	**tab;

	tab = NULL;
	while ((get_next_line(p->fd, &p->line)))
	{
		tab = ft_strsplit(p->line, ' ');
		if (len_tab(tab) == 1)
		{
			if (!(ft_strcmp(tab[0], "objects:")))
			{
				count_objects(p, file, p->line);
				alloc_obj_memory(p, w);
				break ;
			}
		}
		free_tab(tab);
		tab = NULL;
	}
}

int		read_file(char *file, t_data *p, t_world *w)
{
	char	**tab;
	int		i = 0;

	tab = NULL;
	init_parse(p, w);
	if ((p->fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl("\nInvalid file\n");
		exit (-1);
	}
	get_next_line(p->fd, &p->line);
	if ((ft_strcmp(p->line, "---")))
	{
		ft_putendl("\nInvalid file (no ---)\n");
		exit (-1);
	}
	start_count_obj(p, file, w);
	p->fd = open(file, O_RDONLY);
	get_next_line(p->fd, &p->line);
	//printf("line1: %s\n", p->line);
	get_next_line(p->fd, &p->line);
	//printf("line2: %s\n", p->line);
	//get_next_line(p->fd, &p->line); // simple2.yml will work if this is commented
	//printf("i before = %d\n", i);
	while ((get_next_line(p->fd, &p->line)))
	{
		printf("\n\nline in beginning of while: %s\n\n", p->line);
		tab = ft_strsplit(p->line, ' ');
		/*if (len_tab(tab) == 0)
		{
			free_tab(tab);
			continue ;
		}*/
		//printf("\nTab's len is %d\n\n", len_tab(tab));
		if ((len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-")) && !(ft_strcmp(tab[1], "object:"))) || !(strcmp_v2(p->line, "objects:")))
		{
			get_next_line(p->fd, &p->line);
			free_tab(tab);
			tab = NULL;
			tab = ft_strsplit(p->line, ' ');
			if (len_tab(tab) == 2)
			{
				p->tab = (char**)malloc(sizeof(char) * 2);
				p->tab[0] = ft_strdup(tab[0]);
				p->tab[1] = ft_strdup(tab[1]);
				while (!(ft_strcmp(p->tab[0], "type:")) && i < p->obj_n)
				{
					i++;
					check_type(p, w, p->tab);
				}
			}
			else
				exit(err_wrong_format());
		}
		//else
		//	free_tab(tab);
		//p->tab = NULL;
		//if (!(ft_strcmp(p->line, "lights:")) || (len_tab(tab) == 2 && ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:")))
		if (!(strcmp_v2(p->line, "lights:")) || (len_tab(tab) == 2 && ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:")))
		{
			ft_putendl("in if lights");
			//printf("\ntab in if lights: %s, %s\n\n", tab[0], tab[1]);
			if (!(strcmp_v2(p->line, "lights:")))
			{
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (len_tab(tab) == 2 && (ft_strcmp(tab[0], "-") && (ft_strcmp(tab[1], "light:"))))
			{
				ft_putendl("\nin if !(ft_strequ(tab[0], -) && !(ft_strequ(tab[1], light:))\n");
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (len_tab(tab) == 2 && ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:"))
			{
				ft_putendl("\nin if ft_strequ(tab[0], -) && ft_strequ(tab[1], light:)\n");
				p->tab = NULL;
				parse_lights(p, w);
			}
		}
		p->tab = NULL;
		//if (!(ft_strcmp(p->line, "cameras:")))
		//if (!(ft_strcmp(tab[0], "cameras:")))
		if (!(strcmp_v2(p->line, "cameras:")) || (len_tab(tab) == 2 && !(ft_strcmp(tab[0], "-")) && !(ft_strcmp(tab[1], "camera:"))))
		{
			//get_next_line(p->fd, &p->line);
			//tab = ft_strsplit(p->line, ' ');
			if (/*len_tab(tab) == 2 && */(ft_strcmp(tab[0], "-") && (ft_strcmp(tab[1], "camera:"))))
			{
				//ft_putendl("\nin if !(ft_strequ(tab[0], -) && !(ft_strequ(tab[1], light:))\n");
				get_next_line(p->fd, &p->line);
				tab = ft_strsplit(p->line, ' ');
			}
			if (ft_strequ(tab[0], "-") && ft_strequ(tab[1], "camera:"))
			{
				p->cam_num++;
				p->tab = NULL;
				//get_next_line(p->fd, &p->line);
				parse_cameras(p, w);
			}
		}
		//i++;
		//else
		//get_next_line(p->fd, &p->line);
	}
	//printf("i = %d\n", i);
	//if (!p->camera.cam)
	//	return (error_output(NO_CAMERA));
	//init(p);
	//close(p->fd);
	return (0);
}