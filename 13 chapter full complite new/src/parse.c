/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 20:14:25 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/21 23:34:38 by mgalt            ###   ########.fr       */
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
	while (tab[i] != 0)
		i++;
	return (i);
}

int		check_make_obj(char **tab)
{
	if (!(ft_strequ(tab[0], "-")) &&!(ft_strequ(tab[1], "object:")) &&
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
	//ft_putendl("check_type");

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
		push_obj((void*)(&w->pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, w, &w->pl[i].m);
		i++;
	}
	i = 0;
	while (i < p->sp_num)
	{
		push_obj((void*)(&w->s[i]), &normal_at_sp, &intersect_sp, &shade_hit_sp, w, &w->s[i].m);
		i++;
	}
	i = 0;
	while (i < p->cone_num)
	{
		push_obj((void*)(&w->cone[i]), &normal_at_cone, &intersect_cone, &shade_hit_cone, w, &w->cone[i].m);
		i++;
	}
	i = 0;
	while (i < p->cyl_num)
	{
		push_obj((void*)(&w->cyl[i]), &normal_at_cyl, &intersect_cyl, &shade_hit_cyl, w, &w->cyl[i].m);
		i++;
	}
	i = 0;
	while (i < p->cube_num)
	{
		push_obj((void*)(&w->cub[i]), &normal_at_cube, &intersect_cube, &shade_hit_cube, w, &w->cub[i].m);
		i++;
	}
	i = 0;
	while (i < p->tri_num)
	{
		push_obj((void*)(&w->trian[i]), &normal_at_trian, &intersect_trian, &shade_hit_trian, w, &w->trian[i].m);
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

int		read_file(char *file, t_data *p, t_world *w)
{
	char	**tab;
	int		i = 0;

	tab = NULL;
	//ft_putendl("read_file");
	init_parse(p, w);
	if ((p->fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl("\nInvalid file\n");
		exit (-1);
	}
	get_next_line(p->fd, &p->line);
	//ft_putendl("1");
	if ((ft_strcmp(p->line, "---")))
	{
		ft_putendl("\nInvalid file (no ---)\n");
		exit (-1);
	}
	get_next_line(p->fd, &p->line);
	//ft_putendl("2");
	tab = ft_strsplit(p->line, ' ');
	if (!(ft_strcmp(tab[0], "objects:")))
	{
		//printf("line: %s\n", p->line);
		//if ((get_next_line(p->fd, &p->line)) && !(ft_strcmp(p->line, "\n")))
		//	skip_empty_lines(p);
		count_objects(p, file, p->line);
		alloc_obj_memory(p, w);
		//w->pl->pattern = 0;
	}
	free_tab(tab);
	tab = NULL;

	//ft_putendl("before fd open");

	p->fd = open(file, O_RDONLY);

	//ft_putendl("after fd open");
	get_next_line(p->fd, &p->line);
	get_next_line(p->fd, &p->line);
	//get_next_line(p->fd, &p->line); // simple2.yml will work if this is commented

	//ft_putendl("after 3 gnls");
	while (p->line && (get_next_line(p->fd, &p->line) != 0))
	{
		tab = ft_strsplit(p->line, ' ');
		printf("valid len: %d\n", valid_len(&tab, 2, p));
		if (!(valid_len(&tab, 2, p)))
			exit(err_wrong_format());
		if (!(ft_strcmp(tab[1], "object:")))
		{
			get_next_line(p->fd, &p->line);
			free_tab(tab);
			tab = NULL;
			tab = ft_strsplit(p->line, ' ');
			if (!(valid_len(&tab, 2, p)))
				exit(err_wrong_format());
			p->tab = (char**)malloc(sizeof(char) * 2);
			p->tab[0] = ft_strdup(tab[0]);
			p->tab[1] = ft_strdup(tab[1]);
			while (!(ft_strcmp(p->tab[0], "type:")) && i < p->obj_n)
			{
				//ft_putendl("if before check type");
				i++;
				check_type(p, w, p->tab);
				//free_tab(tab);
				//tab = NULL;
			}
			//print_parameters(w, p);
		}
		//ft_putendl("out of if");
		//printf("line before lights: \"%s\"\n", p->line);
		//free_tab(p->tab);
		p->tab = NULL;
		//while ()
		if (!(ft_strcmp(p->line, "lights:")))
		{
			//ft_putendl("if lights");
			get_next_line(p->fd, &p->line);
			tab = ft_strsplit(p->line, ' ');
			if (ft_strequ(tab[0], "-") && ft_strequ(tab[1], "light:"))
			{
				//free_tab(p->tab);
				p->tab = NULL;
				//get_next_line(p->fd, &p->line);
				parse_lights(p, w);
			}
		}
		//printf("line after lights: \"%s\"\n", p->line);
		p->tab = NULL;
		//printf("line after lights 2: \"%s\"\n", p->line);
		if (!(ft_strcmp(p->line, "cameras:")))
		{
			
			//ft_putendl("if cameras");

			get_next_line(p->fd, &p->line);
			tab = ft_strsplit(p->line, ' ');
			if (ft_strequ(tab[0], "-") && ft_strequ(tab[1], "camera:"))
			{
				p->cam_num++;
				//free_tab(p->tab);
				p->tab = NULL;
				//get_next_line(p->fd, &p->line);
				parse_cameras(p, w);
			}
		}
		else
			get_next_line(p->fd, &p->line);
	}
	//pushing_objects(p, w);
	/*i = 0;
	while (i < p->pl_num)
	{
		push_obj((void*)(&w->pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, w, &w->pl[i].m);
		i++;
	}
	i = 0;
	while (i < p->sp_num)
	{
		push_obj((void*)(&w->s[i]), &normal_at_sp, &intersect_sp, &shade_hit_sp, w, &w->s[i].m);
		i++;
	}*/
	//if (!p->camera.cam)
	//	return (error_output(NO_CAMERA));
	//init(p);
	//close(p->fd);
	return (0);
}